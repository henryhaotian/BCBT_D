#include <iostream>
//#include <behavior_tree.h>
#include <youbot_nodes.h>
#include <vrep_utilities.h>
std::string checknode = "";
BT::Pick::Pick(std::string name) : ActionNode::ActionNode("Pick "+name)
{
    name_ = name;
}

BT::ReturnStatus BT::Pick::Tick()
{
    std::cout << "Execute: Pick " <<  name_ << std::endl;
    vrep_utilities::Pick(name_);
    return BT::RUNNING;
}

void BT::Pick::Halt()
{
    std::cout << "Halt: Pick " << name_ << std::endl;
    set_status(BT::HALTED);
}

BT::IsObjectOnHand::IsObjectOnHand(std::string name) : ConditionNode::ConditionNode("IsObjectOnHand "+name)
{
    name_ = name;
}

BT::ReturnStatus BT::IsObjectOnHand::Tick()
{
    std::cout << "Check: IsObjectOnHand " << name_ << std::endl;
    if (vrep_utilities::IsObjectOnHand(name_))
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }
}

BT::IsHandEmpty::IsHandEmpty(std::string name) : ConditionNode::ConditionNode("IsHandEmpty "+name)
{
    name_ = name;
}

BT::ReturnStatus BT::IsHandEmpty::Tick()
{
    std::cout << "Check: IsHandEmpty " << name_ << std::endl;
    if (vrep_utilities::IsHandEmpty())
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }
}

BT::IsFreeToObject::IsFreeToObject(std::string name) : ConditionNode::ConditionNode("IsFreeToObject "+name)
{
    name_ = name;
}

BT::ReturnStatus BT::IsFreeToObject::Tick()
{
    std::cout << "Check: IsFreeToObject " << name_ << std::endl;
    if (vrep_utilities::IsFreeToObject(name_))
    {
        checknode = "";
        return BT::SUCCESS;
    }
    else
    {
        std::string tem = "IsFreeToObject,";
        tem.append(name_);
        checknode = tem;
        return BT::FAILURE;
    }

}

BT::Place::Place(std::string name,std::string goal) : ActionNode::ActionNode("IsObjectOnGoal "+name+","+goal)
{
    name_ = name;
    goal_ = goal;
}

BT::ReturnStatus BT::Place::Tick()
{
    std::cout << "Execute: Place " << name_ << "," << goal_ << std::endl;
    vrep_utilities::Place(name_,goal_);
    return BT::RUNNING;
}

void BT::Place::Halt()
{
    std::cout << "Halt: Place " << name_ << "," << goal_ << std::endl;
    set_status(BT::HALTED);
}

BT::IsObjectOnGoal::IsObjectOnGoal(std::string name,std::string goal) : ConditionNode::ConditionNode("IsObjectOnGoal "+name+","+goal)
{
    name_ = name;
    goal_ = goal;
}

BT::ReturnStatus BT::IsObjectOnGoal::Tick()
{
    std::cout << "Check: IsObjectOnGoal " << name_ << "," << goal_ << std::endl;
    if (vrep_utilities::IsObjectOnGoal(name_,goal_))
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }
}

BT::IsFreeToGoal::IsFreeToGoal(std::string name) : ConditionNode::ConditionNode("IsFreeToGoal "+name)
{
    name_ = name;
}

BT::ReturnStatus BT::IsFreeToGoal::Tick()
{
    std::cout << "Check: IsFreeToGoal " << name_ << std::endl;
    if (vrep_utilities::IsFreeToGoal(name_))
    {
        return BT::SUCCESS;
    }
    else
    {
        return BT::FAILURE;
    }
}

BT::ClearPathTo::ClearPathTo(std::string name) : ActionNode::ActionNode("ClearPathTo "+name)
{
    name_ = name;
}

BT::ReturnStatus BT::ClearPathTo::Tick()
{
    std::cout << "Execute: ClearPathTo " << name_ << std::endl;
    vrep_utilities::ClearPathTo(name_);
    return BT::RUNNING;
}

void BT::ClearPathTo::Halt()
{
std::cout << "Halt: ClearPathTo " << name_ << std::endl;
set_status(BT::HALTED);
}

BT::DropObject::DropObject(std::string name) : ActionNode::ActionNode("DropObject "+name)
{
    name_ = name;
}

BT::ReturnStatus BT::DropObject::Tick()
{
    std::cout << "Execute: DropObject " << name_ << std::endl;
    vrep_utilities::DropObject(name_);
    return BT::RUNNING;
}

void BT::DropObject::Halt()
{
std::cout << "Halt: DropObject " << name_ << std::endl;
set_status(BT::HALTED);
}



