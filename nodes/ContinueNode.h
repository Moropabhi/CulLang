#pragma once
#include "Node.h"
namespace CulLang
{
    class ContinueNode : public Node
    {
    public:
        ContinueNode()=default;

        virtual Str getInStr() override;
        virtual std::array<Position, 2> getPos() override;

        virtual NodeType getType() override {return Break;}

        virtual Ref<Object> visit() override;

        static bool shouldContinue;
    };

    bool ContinueNode::shouldContinue;

    Str ContinueNode::getInStr()
    {
        return "continue";
    }

    std::array<Position, 2> ContinueNode::getPos()
    {
        return {};
    }

    Ref<Object> ContinueNode::visit()
    {
        shouldContinue=true;
        return Object::NONE;
    }
}
