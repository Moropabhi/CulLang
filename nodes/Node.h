#pragma once

#include "../datatypes/Object.h"
#include "../Token.h"

class Cul;

namespace CulLang {

	enum NodeType {
		ValueNode,
		UnaryNode,
		BinaryNode,
		VarAllocatingNode,
		VarAccessingNode,
		AssignmentNode,
		PrintingNode,
		AugumentedNode,
		blockNode,
		IfblockNode,
		WhileblockNode,
		ForblockNode,
		FuncblockNode,
		CallableNode
	};

	class Node 
	{

	public:
		Node(const Token* tok);
		Node()=default;
		virtual ~Node();

		/*
			This is for debugging purposes.
			\returns \n the node in a readable format
		*/
		virtual Str getInStr();
		/*
			\returns Type of the node
		*/
		virtual NodeType getType();
		/*
			\returns Position of the node
		*/
		virtual std::array<Position, 2> getPos();

		/*
			Sets the value of the node
		*/
		virtual void SetValue(const Token* val);

		/*
			Evaluate the node
			\returns an object contaiing the value
		*/
		virtual Ref<Object> visit();
		virtual std::string translateToC();
	protected:
		NodeType type = ValueNode;
		const Token* value = nullptr;
	};
	using NumberNode = Node;
	using IntNode = Node;
	using FloatNode = Node;
	using StrNode = Node;

}

namespace CulLang {

	Node::Node(const Token* tok)
		:value(tok)
	{}
	Node::~Node()
	{
	}

	Str Node::getInStr()
	{
		return value->getTypeStr();
	}

	NodeType Node::getType()
	{
		return type;
	}
	std::array<Position, 2> Node::getPos()
	{
		return value->getPos();
	}
	void Node::SetValue(const Token* val)
	{
		value = val;
	}
	Ref<Object> Node::visit()
	{
		return value->getValueConverted();
	}
	std::string Node::translateToC()
	{
		return value->getConvertedtoC();
	}

}