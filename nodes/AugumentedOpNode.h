#pragma once

#include "Node.h"
namespace CulLang
{
	class AugumentedOperatorNode : public Node
	{
	public:
		const Token& var_name;
        Position left_pos;
		Ref<Node> right;

		AugumentedOperatorNode(const Token* left, const Token *op,const Ref<Node> &right);
		virtual ~AugumentedOperatorNode() override;

		virtual std::string getInStr() override;
		NodeType getType() override;
		virtual std::array<Position, 2> getPos() override;

		virtual Ref<Object> visit() override;
		Ref<Object> callOperation(TokenType type, const Ref<Object> &L, const Ref<Object> &R);
	};
}
namespace CulLang
{

	AugumentedOperatorNode::AugumentedOperatorNode(const Token* left, const Token *op, const Ref<Node> &right)
		: var_name(*left),left_pos(left->getPos()[0]), Node(op), right(right)
	{
		type = AugumentedNode;
	}

	AugumentedOperatorNode::~AugumentedOperatorNode() {}

	std::string AugumentedOperatorNode::getInStr()
	{
		return var_name.getVal() + " " + Node::getInStr() + " " + right->getInStr() ;
	};

	NodeType AugumentedOperatorNode::getType()
	{
		return AugumentedNode;
	}

	std::array<Position, 2> AugumentedOperatorNode::getPos()
	{
		return {left_pos, right->getPos()[1]};
	}

	Ref<Object> AugumentedOperatorNode::visit()
	{
		auto R = right->visit();
		return callOperation(value->getType(), SymbolTable::getGlobal().getValue(var_name), R);
	}

	Ref<Object> AugumentedOperatorNode::callOperation(TokenType type, const Ref<Object> &L, const Ref<Object> &R)
	{
		switch (type)
		{
		case culIPlus:
			L->__iadd__(R);
			break;
		case culIMinus:
			L->__isub__(R);
			break;
		case culIMul:
			L->__imul__(R);
			break;
		case culIDiv:
			L->__idiv__(R);
			break;
		case culIPower:
			L->__ipow__(R);
			break;
		case culIMod:
			L->__imod__(R);
			break;
		default:
			ErrorHandler::raiseError({ErrorType::FeatureNotImplementedYet,getPos(),"This operation is not implemented yet"});
			return Object::NONE;
		}

		if (ErrorHandler::anyStackErrors())
		{
			auto &errs = ErrorHandler::getStack();
			for (auto &i : errs)
				i.setPos(getPos());
			ErrorHandler::raiseStackAll();
		}

		return Object::NONE;
	}

}