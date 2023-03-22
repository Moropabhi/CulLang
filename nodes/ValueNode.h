	#include "Node.h"
    
namespace CulLang{
    class ValueNode : public Node
	{

	public:
		ValueNode(const Token* tok);
		ValueNode()=default;
		virtual ~ValueNode()=default;

		/*
			This is for debugging purposes.
			\returns \n the ValueNode in a readable format
		*/
		virtual Str getInStr(){
		return token.getTypeStr();
	}
		virtual NodeType getType() override { return ValueNode_;}
		/*
			\returns Position of the ValueNode
		*/
		virtual std::array<Position, 2> getPos();

		/*
			Sets the Token of the ValueNode
		*/
		virtual void SetToken(const Token* val);
		/*
			Get the value of the ValueNode
		*/
		virtual const Token* GetToken(){return &token;}

		/*
			Evaluate the ValueNode
			\returns an object contaiing the value
		*/
		virtual Ref<Object> visit();

		/*
			Translating the tree in C code
			TODO
		*/
		virtual std::string translateToC(){return "";}

        private:
        Token token;

	};


	ValueNode::ValueNode(const Token* tok)
		:token(std::move(*tok))
	{}
	
	std::array<Position, 2> ValueNode::getPos()
	{
		return token.getPos();
	}
	void ValueNode::SetToken(const Token* val)
	{
		token = *val;
	}
	Ref<Object> ValueNode::visit()
	{
		DEBUG_LOG(token.getVal());
		return token.getValueConverted();
	}
}