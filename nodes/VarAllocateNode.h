#pragma once
#include "Node.h"
namespace CulLang 
{
	class VarAccessNode;
	class AssignmentOperatorNode;
	class VarAllocateNode : public Node
	{
	public:
		VarAllocateNode(const Token* v, Ref<Node> expr)
			:var_tok(std::move(*v)),expr(expr)
		{}

		virtual Str getInStr()override;
		virtual std::array<Position, 2> getPos()override;
		virtual NodeType getType() { return VarAllocatingNode; }

		virtual Ref<Object> visit() override;
	private:
		Ref<Node> expr;
		Token var_tok;
	};
}


namespace CulLang 
{

    Str VarAllocateNode::getInStr()
    {
        return "let "+var_tok.getVal() + " = "+expr->getInStr();
    }

    std::array<Position, 2> VarAllocateNode::getPos()
    {
        return { var_tok.getPos()[0],expr->getPos()[1] };
    }

    Ref<Object> VarAllocateNode::visit()
    {

        auto res = expr->visit();
        SymbolTable::getGlobal().addVariable( var_tok, res);
        return Object::NONE;
    }
}
