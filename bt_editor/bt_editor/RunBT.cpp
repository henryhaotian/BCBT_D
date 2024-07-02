#include "RunBT.h"
extern "C" {
    #include "extApi.h"
}
RunBT::RunBT()
{
    vrep_utilities::init();
    first_readtree = true;
    max_node_num = 0;
    timer_start = true;
    timer_end = true;
    BT_duration= 0;
    iteration_count = 0;
    vrep_utilities::startSimulation();
}

RunBT::~RunBT()
{

}

void RunBT::GetScene(QtNodes::FlowScene *scene_)
{
    scene = scene_;
}

void RunBT::GetXMLPath(QString fileName_)
{
    fileName = fileName_;
}

void RunBT::run()
{
    if (timer_start)
    {
        time_for_BT.start();
        timer_start = false;
    }
    
    QtNodes::Node* root;
    std::vector<QtNodes::Node*> roots = findRoots(*scene);

    if (roots.empty())
    {
        std::cout << "No Root found" << std::endl;
        return;
    }

    root= roots.at(0);

    ClearNodeNum();
    BT::TreeNode* bt_root = getBTObject(*scene, *root);

    while (getMode() == 1)
    {
        std::cout << std::endl;
        std::cout << "Ticking the root node !" << std::endl;

        // Ticking the root node
        BT::ReturnStatus result = bt_root->Tick();

        scene->update();

        for (auto &it : scene->nodes())
        {
            QtNodes::Node *node = it.second.get();
            node->nodeGraphicsObject().update();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // std::cout << "BT node num: " << node_num << std::endl;
        // if (max_node_num < node_num)
        // {
        //     max_node_num = node_num;
        // }
        // std::cout << "Max BT node num: " << max_node_num << std::endl;

        //ReviseSubtree
        if (result == BT::RUNNING)
        {
            extern std::string checknode;
            if (checknode != "")
            {
                QString Q_checknode = QString::fromStdString(checknode);
                QStringList QL_checknode = Q_checknode.split(",");
                std::string res =  vrep_utilities::GetCurrentObstacle(QL_checknode[1].toStdString());
                QString obstacle_set = QString::fromStdString(res);
                QStringList NodesByHeuristics = Heuristics(obstacle_set,QL_checknode[1]);
                if (!NodesByHeuristics.isEmpty())
                {
                    bool result = ReviseSubtree(NodesByHeuristics,QL_checknode[0],QL_checknode[1]);
                    if (result)
                    {
                        emit ReExecute();
                        return;
                    }
                }
            }
        }
        if (result == BT::FAILURE)
        {
            std::cout << "BT Return Failure, Failed Node: " << bt_root->last_failed_Node << std::endl;
            std::cout << "Halting the BT" << std::endl;
            bt_root->Halt();
            if(!UpdateTree(QString::fromStdString(bt_root->last_failed_Node)))
            {
                std::cout << "Update BT Failed" << std::endl;
                return;
            }
            else
            {
                std::cout << "Update BT Success" << std::endl;
                iteration_count++;
                emit ReExecute();
                return;
            }
        }
        if (result == BT::SUCCESS)
        {
            if (timer_end)
            {
                BT_duration = time_for_BT.elapsed();
                timer_end = false;
            }
            qDebug() << "Time: " << BT_duration << "ms\n";
            std::cout << "Iteration : " << iteration_count << std::endl;
            int node_num = getNodeNum();
            std::cout << "BT node num: " << node_num << std::endl;
        }
    }
    std::cout << "Halting the BT" << std::endl;
    bt_root->Halt();
}

bool RunBT::ReviseSubtree(QStringList prompts, QString node_name, QString node_attribute)
{
    QStringList Nodes;
    QDomDocument doc;
    if(!ReadTree(doc))
    {
        return false;
    }
    QDomElement root = doc.documentElement();

    if( root.tagName() != "root" )
    {
        qDebug() << "Expecting the node <root> in the XML \n";
        return false;
    }

    QDomElement behaviortree_root = root.firstChildElement("BehaviorTree");
    QDomNode node = behaviortree_root.firstChild();

    QDomNode located_node;
    first_locate_node = true;
    LocateNode(node_name,node_attribute,node,located_node);
    QDomNode sibling_node = located_node.nextSibling();
    QDomNode first_node = sibling_node.firstChild();
    if (first_node.hasChildNodes())
    {
        QDomNode f_first_node = first_node.firstChild();
        if (f_first_node.toElement().tagName() == "IsObjectOnGoal")
        {
            return false;
        }
        else
        {
            QDomElement element_p = doc.createElement("IsObjectOnGoal");
            element_p.setAttribute("text", prompts[0]);
            sibling_node.insertBefore(element_p,first_node);
        }
    }
    else
    {
        QDomElement element_p = doc.createElement("IsObjectOnGoal");
        element_p.setAttribute("text", prompts[0]);
        sibling_node.insertBefore(element_p,first_node);
    }
    
    if(!WriteTree(doc))
    {
        return false;
    }
    return true;
}

bool RunBT::UpdateTree(QString fail_node)
{
    QStringList node_param = fail_node.split(" ");

    QDomDocument doc;
    if(!ReadTree(doc))
    {
        return false;
    }
    QDomElement root = doc.documentElement();

    if( root.tagName() != "root" )
    {
        qDebug() << "Expecting the node <root> in the XML \n";
        return false;
    }

    QDomElement behaviortree_root = root.firstChildElement("BehaviorTree");
    QDomNode node = behaviortree_root.firstChild();

    //get all local goals
    localgoals = node.childNodes();

    QDomNode failed_node;
    first_locate_node = true;
    LocateNode(node_param[0],node_param[1],node,failed_node);

    QDomNode parent_node;
    parent_node = failed_node.parentNode();

    QDomElement new_subtree = ExpandTree(node_param[0],node_param[1],doc);
    parent_node.toElement().replaceChild(new_subtree,failed_node.toElement());
    
    if(!WriteTree(doc))
    {
        return false;
    }
    return true;
}

QDomElement RunBT::ExpandTree(QString node_name, QString node_attribute,QDomDocument& doc)
{
    QDomElement fall_element = doc.createElement("Fallback");
    fall_element.setAttribute("text", "IFTHENELSE");

    if(node_name == "IsObjectOnHand")
    {
        QDomElement element_1 = doc.createElement(node_name);
        element_1.setAttribute("text", node_attribute);
        fall_element.appendChild(element_1);

        QDomElement seq_element = doc.createElement("Sequence");
        seq_element.setAttribute("text", "IFTHENELSE");
        fall_element.appendChild(seq_element);

        QDomElement element_2 = doc.createElement("IsFreeToObject");
        element_2.setAttribute("text", node_attribute);
        seq_element.appendChild(element_2);

        QDomElement element_3 = doc.createElement("IsHandEmpty");
        element_3.setAttribute("text", node_attribute);
        seq_element.appendChild(element_3);

        QDomElement element_4 = doc.createElement("Pick");
        element_4.setAttribute("text", node_attribute);
        seq_element.appendChild(element_4);
    }
    else if (node_name == "IsObjectOnGoal")
    {
        QStringList attribute = node_attribute.split(",");

        QDomElement element_1 = doc.createElement(node_name);
        element_1.setAttribute("text", node_attribute);
        fall_element.appendChild(element_1);

        QDomElement seq_element = doc.createElement("Sequence");
        seq_element.setAttribute("text", "IFTHENELSE");
        fall_element.appendChild(seq_element);

        QDomElement element_2 = doc.createElement("IsFreeToGoal");
        element_2.setAttribute("text", attribute[1]);
        seq_element.appendChild(element_2);

        QDomElement element_3 = doc.createElement("IsObjectOnHand");
        element_3.setAttribute("text", attribute[0]);
        seq_element.appendChild(element_3);

        QDomElement element_4 = doc.createElement("Place");
        element_4.setAttribute("text", node_attribute);
        seq_element.appendChild(element_4);
    }
    else if(node_name == "IsFreeToObject")
    {
        QDomElement element_1 = doc.createElement(node_name);
        element_1.setAttribute("text", node_attribute);
        fall_element.appendChild(element_1);

        QDomElement seq_element = doc.createElement("Sequence");
        seq_element.setAttribute("text", "IFTHENELSE");
        fall_element.appendChild(seq_element);

        //Heuristics
        std::string res =  vrep_utilities::GetCurrentObstacle(node_attribute.toStdString());
        QString obstacle_set = QString::fromStdString(res);
        QStringList NodesByPrompts = Heuristics(obstacle_set,node_attribute);
        if (!NodesByPrompts.isEmpty())
        {
            for (int i = 0; i < NodesByPrompts.count(); i++)
            {
                QDomElement element_p = doc.createElement("IsObjectOnGoal");
                element_p.setAttribute("text", NodesByPrompts[i]);
                seq_element.appendChild(element_p);
            }
        }
        
        QDomElement element_2 = doc.createElement("IsHandEmpty");
        element_2.setAttribute("text", node_attribute);
        seq_element.appendChild(element_2);

        QDomElement element_3 = doc.createElement("ClearPathTo");
        element_3.setAttribute("text", node_attribute);
        seq_element.appendChild(element_3);

    }
    else if (node_name == "IsFreeToGoal")
    {
        QDomElement element_1 = doc.createElement(node_name);
        element_1.setAttribute("text", node_attribute);
        fall_element.appendChild(element_1);

        QDomElement seq_element = doc.createElement("Sequence");
        seq_element.setAttribute("text", "IFTHENELSE");
        fall_element.appendChild(seq_element);

        QDomElement element_2 = doc.createElement("IsHandEmpty");
        element_2.setAttribute("text", node_attribute);
        seq_element.appendChild(element_2);

        QDomElement element_3 = doc.createElement("ClearPathTo");
        element_3.setAttribute("text", node_attribute);
        seq_element.appendChild(element_3);
    }
    else if (node_name == "IsHandEmpty")
    {
        QDomElement element_1 = doc.createElement(node_name);
        element_1.setAttribute("text", node_attribute);
        fall_element.appendChild(element_1);

        QDomElement element_2 = doc.createElement("DropObject");
        element_2.setAttribute("text", node_attribute);
        fall_element.appendChild(element_2);

    }
    
    return fall_element;
}

QStringList RunBT::Heuristics(QString obstacle_set, QString node_attribute)
{
    QStringList Nodes;
    QStringList obstacle = obstacle_set.split(",");
    for (int i = 0; i < obstacle.count(); i++)
    {
        for (int j = 0; j < localgoals.count(); j++)
        {
            QString textContent = localgoals.at(j).toElement().attribute("text");
            QStringList localgoal = textContent.split(",");
            if (obstacle[i] == localgoal[0])
            {
                if (node_attribute == localgoal[1])
                {
                    break;
                }
                Nodes.append(textContent);
            }
        }
    }
    return Nodes;
}

bool RunBT::ReadTree(QDomDocument &doc)
{
    if(first_readtree)
    {
        QStringList file_name = fileName.split("-");
        fileName = file_name[0]+".xml";
        // qDebug() << fileName << "\n";
    }
    QFile file(fileName);
    if(! file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Open XML File False \n";
        return false;
    }
    if(!doc.setContent(&file))
    {
        qDebug() << "Read XML False \n";
        file.close();
        return false;
    }
    file.close();
    if(first_readtree)
    {
        QStringList file_name = fileName.split(".");
        fileName = file_name[0]+"-update.xml";
        first_readtree = false;
    }
    return true;
}

bool RunBT::WriteTree(QDomDocument doc)
{
   QFile file_t(fileName);
    if(!file_t.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Open XML File False \n";
        return false;
    }
    QTextStream ts(&file_t);
    ts.reset();
    // ts.setCodec("utf-8");
    doc.save(ts,4,QDomNode::EncodingFromTextStream);
    file_t.close();
    return true;
}

void RunBT::LocateNode(QString node_name, QString node_attribute,const QDomNode &node, QDomNode &fail_node)
{
    if(node.hasChildNodes())
    {
        for (int i = 0; i < node.childNodes().size(); i++)
        {
            LocateNode(node_name, node_attribute, node.childNodes().at(i),fail_node);   
        }
    }
    else
    {
        if (node.toElement().tagName() == node_name)
        {
            if (node.toElement().attribute("text") == node_attribute)
            {
                qDebug() << "Locate the Node: " << node.toElement().tagName() << " " <<node.toElement().attribute("text");
                if (first_locate_node)
                {
                    fail_node =  node;
                    first_locate_node = false;
                }
            }
        }
    }
}
