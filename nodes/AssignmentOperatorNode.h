#pragma once 
#include "Node.h"
namespace CulLang
{

	class AssignmentOperatorNode : public Node
	{
	public:
		AssignmentOperatorNode(const Token* v, Ref<Node> expr)
			:Node(v), expr(expr)
		{
			type = AssignmentNode;

		}

		virtual Str getInStr()override;
		virtual std::array<Position, 2> getPos()override;

		virtual Ref<Object> visit() override;
	private:

		Ref<Node> expr;
	};
}

namespace CulLang
{

    Str AssignmentOperatorNode::getInStr()
    {
        return value->getVal() + " = "  + expr->getInStr();
    }

    std::array<Position, 2> AssignmentOperatorNode::getPos()
    {
        return { value->getPos()[0],expr->getPos()[1] };
    }

    Ref<Object> AssignmentOperatorNode::visit()
    {
        auto res = expr->visit();

        SymbolTable::getGlobal().addVariable(*value,res);
        return nullptr;
    }
}