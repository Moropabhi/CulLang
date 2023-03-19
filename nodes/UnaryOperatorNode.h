#pragma once

#include "Node.h" 

namespace CulLang
{
	class UnaryOperatorNode : public Node
	{
	public:
		UnaryOperatorNode(const Token *op, Ref<Node> right);
		virtual ~UnaryOperatorNode();
		virtual std::string getInStr() override;
		virtual NodeType getType();

		virtual std::array<Position, 2> getPos() override;

		virtual Ref<Object> visit() override;
		Ref<Object> callOperation(const Token * str, const Ref<Object> &R);

	private:
		Ref<Node> right;
	};
}
namespace CulLang
{
	UnaryOperatorNode::UnaryOperatorNode(const Token *op, Ref<Node> right)
		: Node(op), right(right)
	{
		type = UnaryNode;
	}
	UnaryOperatorNode::~UnaryOperatorNode()
	{
	}

	std::string UnaryOperatorNode::getInStr()
	{
		if (value->getType() == culIncrement || value->getType() == culDecrement)
			return " ( " + right->getInStr() + " " + Node::getInStr() + " ) ";
		return " ( " + Node::getInStr() + " " + right->getInStr() + " ) ";
	}
	NodeType UnaryOperatorNode::getType()
	{
		return UnaryNode;
	}

	std::array<Position, 2> UnaryOperatorNode::getPos()
	{
		return {value->getPos()[0], right->getPos()[1]};
	}

	Ref<Object> UnaryOperatorNode::visit()
	{
		auto R = right->visit();
		return callOperation(value,R);
	}
	Ref<Object> UnaryOperatorNode::callOperation(const Token* val, const Ref<Object> &R)
	{
		//std::cout<<val->getType()<<'\n';
		switch (val->getType())
		{
		case culPlus:
			R->__plus__();
			break;
		case culMinus:
			R->__minus__();
			break;
		case culIncrement:
			R->__increment__();
			break;
		case culDecrement:
			R->__decrement__();
			break;
		case culKeyword:
			switch(std::find(CulKeywordStr.begin(),CulKeywordStr.end(),val->getVal())-CulKeywordStr.begin())
			{
				case culNot:
					R->__not__();
					break;
				default:
					ErrorHandler::raiseError({ErrorType::FeatureNotImplementedYet,getPos(),"This (keyword) operation is not implemented yet from UnaryOperatorNode"});
					return Object::NONE;
			}
			break;
		
		default:
			ErrorHandler::raiseError({ErrorType::FeatureNotImplementedYet,getPos(),"This operation is not implemented yet from UnaryOperatorNode"});
			return Object::NONE;
		}
		if (ErrorHandler::anyStackErrors())
		{
			auto &errs = ErrorHandler::getStack();
			for (auto &i : errs)
				i.setPos(getPos());
			ErrorHandler::raiseStackAll();
		}

		return R;
	}
}
