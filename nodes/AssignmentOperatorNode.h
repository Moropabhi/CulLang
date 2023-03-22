#pragma once 
#include "Node.h"
namespace CulLang
{

	class AssignmentOperatorNode : public Node
	{
	public:
		AssignmentOperatorNode(const Token* v, Ref<Node> expr)
			:expr(expr),variable_tok(std::move(*v))
		{}

        virtual NodeType getType() { return AssignmentNode;}

		virtual Str getInStr() override;
		virtual std::array<Position, 2> getPos() override;

		virtual Ref<Object> visit() override;
	private:

		Ref<Node> expr;
        Token variable_tok;
	};
}

namespace CulLang
{
    Str AssignmentOperatorNode::getInStr()
    {
        return variable_tok.getVal() + " = "  + expr->getInStr();
    }

    std::array<Position, 2> AssignmentOperatorNode::getPos()
    {
        return { variable_tok.getPos()[0],expr->getPos()[1] };
    }

    Ref<Object> AssignmentOperatorNode::visit()
    {
        auto res = expr->visit();

        SymbolTable::getGlobal().setValue(variable_tok,res);
        return nullptr;
    }
}