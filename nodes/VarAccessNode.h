#pragma once
#include "Node.h"
namespace CulLang
{

	class VarAccessNode : public Node
	{
	public:
		VarAccessNode(const Token* v)
			:Node(v)
		{
			type = VarAccessingNode;
		}

		virtual Ref<Object> visit() override;

		virtual std::string getInStr() override
		{
			return this->value->getVal();
		}

	};
}
namespace CulLang
{
    Ref<Object> VarAccessNode::visit()
    {
        return SymbolTable::getGlobal().getValue(*value);
    }
}
