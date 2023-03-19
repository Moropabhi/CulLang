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
			:Node(v),expr(expr)
		{
			type = VarAllocatingNode;

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

    Str VarAllocateNode::getInStr()
    {
        return "let "+value->getVal() + " = "+expr->getInStr();
    }

    std::array<Position, 2> VarAllocateNode::getPos()
    {
        return { value->getPos()[0],expr->getPos()[1] };
    }

    Ref<Object> VarAllocateNode::visit()
    {

        auto res = expr->visit();
        SymbolTable::getGlobal().addVariable( *value, res);
        //LOG(app->table.getValue(value->getVal()).val << "DONE\n");
        return Object::NONE;
    }
}
