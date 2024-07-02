#pragma once
#include <action_node.h>
#include <condition_node.h>
namespace BT
{
class Pick : public BT::ActionNode
{
public:
    Pick(std::string name);
    ~Pick();
    BT::ReturnStatus Tick();
    void Halt();
private:
    std::string name_;
};

class IsObjectOnHand : public BT::ConditionNode
{
public:
    IsObjectOnHand(std::string name);
    ~IsObjectOnHand();
    BT::ReturnStatus Tick();
private:
   std::string name_;
};

class IsHandEmpty : public BT::ConditionNode
{
public:
    IsHandEmpty(std::string name);
    ~IsHandEmpty();
    BT::ReturnStatus Tick();
private:
    std::string name_;
};

class IsFreeToObject : public BT::ConditionNode
{
public:
    IsFreeToObject(std::string name);
    ~IsFreeToObject();
    BT::ReturnStatus Tick();
private:
   std::string name_;
};

class Place : public BT::ActionNode
{
public:
    Place(std::string name, std::string goal);
    ~Place();
    BT::ReturnStatus Tick();
    void Halt();
private:
   std::string name_;
   std::string goal_;
};

class IsObjectOnGoal : public BT::ConditionNode
{
public:
    IsObjectOnGoal(std::string name, std::string goal);
    ~IsObjectOnGoal();
    BT::ReturnStatus Tick();
private:
   std::string name_;
   std::string goal_;
};

class IsFreeToGoal : public BT::ConditionNode
{
public:
    IsFreeToGoal(std::string name);
    ~IsFreeToGoal();
    BT::ReturnStatus Tick();
private:
   std::string name_;
};

class ClearPathTo : public BT::ActionNode
{
public:
    ClearPathTo(std::string name);
    ~ClearPathTo();
    BT::ReturnStatus Tick();
    void Halt();
private:
    std::string name_;
};

class DropObject : public BT::ActionNode
{
public:
    DropObject(std::string name);
    ~DropObject();
    BT::ReturnStatus Tick();
    void Halt();
private:
    std::string name_;
};

}
