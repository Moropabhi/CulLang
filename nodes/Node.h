#pragma once

#include "../datatypes/Object.h"
#include "../Token.h"

namespace CulLang {

	enum NodeType {
		ValueNode_,
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
		LoopblockNode,
		Break,
		Continue,
		FuncblockNode,
		CallableNode
	};

	class Node 
	{

	public:
		virtual ~Node()=default;

		/*
			This is for debugging purposes.
			\returns \n the node in a readable format
		*/
		virtual Str getInStr() {return "Node";}
		/*
			\returns Type of the node
		*/
		virtual NodeType getType()=0;
		/*
			\returns Position of the node
		*/
		virtual std::array<Position, 2> getPos()=0;

		/*
			Sets the Token of the node
		*/
		virtual void SetToken(const Token* val){}
		/*
			Get the value of the node
		*/
		virtual const Token* GetToken(){return nullptr;}

		/*
			Evaluate the node
			\returns an object contaiing the value
		*/
		virtual Ref<Object> visit()=0;

		/*
			Translating the tree in C code
			TODO
		*/
		virtual std::string translateToC(){return "";}
	};
}