#pragma once

#include "BehaviorTreeNodeModel.h"


class ActionNodeModel : public BehaviorTreeNodeModel
{
public:
    ActionNodeModel():
        BehaviorTreeNodeModel("Action", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::ACTION;
    }
    virtual ~ActionNodeModel() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new ActionNodeModel ); }

    virtual QString name() const override { return QString("Action"); }
//    virtual QString name() const override { return QString("Action"); }
};

class Pick : public BehaviorTreeNodeModel
{
public:
    Pick():
        BehaviorTreeNodeModel("Pick", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::PICK;
    }
    virtual ~Pick() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new Pick ); }

    virtual QString name() const override { return QString("Pick"); }
};

class IsObjectOnHand : public BehaviorTreeNodeModel
{
public:
    IsObjectOnHand():
        BehaviorTreeNodeModel("IsObjectOnHand", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::ISOBJECTONHAND;
    }
    virtual ~IsObjectOnHand() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new IsObjectOnHand ); }

    virtual QString name() const override { return QString("IsObjectOnHand"); }
};

class IsHandEmpty : public BehaviorTreeNodeModel
{
public:
    IsHandEmpty():
        BehaviorTreeNodeModel("IsHandEmpty", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::ISHANDEMPTY;
    }
    virtual ~IsHandEmpty() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new IsHandEmpty ); }

    virtual QString name() const override { return QString("IsHandEmpty"); }
};

class IsFreeToObject : public BehaviorTreeNodeModel
{
public:
    IsFreeToObject():
        BehaviorTreeNodeModel("IsFreeToObject", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::ISFREETOOBJECT;
    }
    virtual ~IsFreeToObject() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new IsFreeToObject ); }

    virtual QString name() const override { return QString("IsFreeToObject"); }
};

class Place : public BehaviorTreeNodeModel
{
public:
    Place():
        BehaviorTreeNodeModel("Place", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::PLACE;
    }
    virtual ~Place() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new Place ); }

    virtual QString name() const override { return QString("Place"); }
};

class IsObjectOnGoal : public BehaviorTreeNodeModel
{
public:
    IsObjectOnGoal():
        BehaviorTreeNodeModel("IsObjectOnGoal", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::ISOBJECTONGOAL;
    }
    virtual ~IsObjectOnGoal() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new IsObjectOnGoal ); }

    virtual QString name() const override { return QString("IsObjectOnGoal"); }
};

class IsFreeToGoal : public BehaviorTreeNodeModel
{
public:
    IsFreeToGoal():
        BehaviorTreeNodeModel("IsFreeToGoal", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::ISFREETOGOAL;
    }
    virtual ~IsFreeToGoal() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new IsFreeToGoal ); }

    virtual QString name() const override { return QString("IsFreeToGoal"); }
};

class ClearPathTo : public BehaviorTreeNodeModel
{
public:
    ClearPathTo():
        BehaviorTreeNodeModel("ClearPathTo", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::CLEARPATHTO;
    }
    virtual ~ClearPathTo() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new ClearPathTo ); }

    virtual QString name() const override { return QString("ClearPathTo"); }
};

class DropObject : public BehaviorTreeNodeModel
{
public:
    DropObject():
        BehaviorTreeNodeModel("DropObject", NodeFactory::get().getActionParameterModel() )
    { }
    int BTType()
    {
        return BT::DROPOBJECT;
    }
    virtual ~DropObject() {}

    virtual unsigned int  nPorts(PortType portType) const override
    { return (portType==PortType::In) ? 1:0; }

    virtual std::unique_ptr<NodeDataModel> clone() const override
    { return  std::unique_ptr<NodeDataModel>( new DropObject ); }

    virtual QString name() const override { return QString("DropObject"); }
};
