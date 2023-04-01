#pragma once
#include "Node.h"
namespace CulLang
{
    class BreakNode : public Node
    {
    public:
        BreakNode()=default;

        virtual Str getInStr() override;
        virtual std::array<Position, 2> getPos() override;

        virtual NodeType getType() override {return Break;}

        virtual Ref<Object> visit() override;

        static bool shouldBreak;
    };

    bool BreakNode::shouldBreak;

    Str BreakNode::getInStr()
    {
        return "break";
    }

    std::array<Position, 2> BreakNode::getPos()
    {
        return {};
    }

    Ref<Object> BreakNode::visit()
    {
        shouldBreak=true;
        return Object::NONE;
    }
}
