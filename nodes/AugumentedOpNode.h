#pragma once

#include "Node.h"
namespace CulLang
{
	class AugumentedOperatorNode : public Node
	{
	public:
		AugumentedOperatorNode(const Token* left, const Token *op,const Ref<Node> &right);
		virtual ~AugumentedOperatorNode() override;

		virtual std::string getInStr() override;
		NodeType getType() override;
		virtual std::array<Position, 2> getPos() override;

		virtual Ref<Object> visit() override;
		Ref<Object> callOperation(TokenType type, const Ref<Object> &L, const Ref<Object> &R);
	private:
		Token var_tok;
        TokenType operator_;
		Ref<Node> right;
	};
}
namespace CulLang
{

	AugumentedOperatorNode::AugumentedOperatorNode(const Token* left, const Token *op, const Ref<Node> &right)
		: var_tok(std::move(*left)), operator_(op->getType()), right(right)
	{
	}

	AugumentedOperatorNode::~AugumentedOperatorNode() {}

	std::string AugumentedOperatorNode::getInStr()
	{
		return var_tok.getVal() + " " + Node::getInStr() + " " + right->getInStr() ;
	};

	NodeType AugumentedOperatorNode::getType()
	{
		return AugumentedNode;
	}

	std::array<Position, 2> AugumentedOperatorNode::getPos()
	{
		return {var_tok.getPos()[0], right->getPos()[1]};
	}

	Ref<Object> AugumentedOperatorNode::visit()
	{
		auto R = right->visit();
		return callOperation(operator_, SymbolTable::getGlobal().getValue(var_tok), R);
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