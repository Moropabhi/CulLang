#pragma once
#include "Node.h"
namespace CulLang
{
    class PrintNode : public Node
    {
    public:
        PrintNode(Ref<Node> expr)
            :expr(expr)
        {
            type = PrintingNode;
        }

        virtual Str getInStr() override;
        virtual std::array<Position, 2> getPos() override;

        virtual Ref<Object> visit() override;

    private:
        Ref<Node> expr;
    };
}

namespace CulLang
{

    Str PrintNode::getInStr()
    {
        return "print " + expr->getInStr();
    }

    std::array<Position, 2> PrintNode::getPos()
    {
        return {value->getPos()[0], expr->getPos()[1]};
    }

    Ref<Object> PrintNode::visit()
    {
        auto res = expr->visit();
        std::cout << res->asAStr() << '\n';
        return Object::NONE;
    }
}
