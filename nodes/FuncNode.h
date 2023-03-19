#pragma once
#include "../Utilities.h"
#include "Node.h"
namespace CulLang {
class FuncNode : public Node {
  public:
    const Ref<Node> expression = nullptr;

    FuncNode(const Token* name,const Ref<Node> &expression);
    virtual ~FuncNode() override;

    virtual std::string getInStr() override;
    NodeType getType() override;
    virtual std::array<Position, 2> getPos() override;

    virtual Ref<Object> visit() override;
};
} // namespace CulLang
namespace CulLang {

FuncNode::FuncNode(const Token* name,const Ref<Node> &expression)
    : expression(expression), Node(name) {
    type = FuncblockNode;
}

FuncNode::~FuncNode() {}

std::string FuncNode::getInStr() {
    auto out =
        "while "" : " + expression->getInStr();
    // if(elseExpression)
    // {
    //     out += " else : " + elseExpression->getInStr();
    // }
    return out;
};

NodeType FuncNode::getType() { return FuncblockNode; }

std::array<Position, 2> FuncNode::getPos() { return value->getPos(); }

Ref<Object> FuncNode::visit() {

    
    // if (elseExpression)
    //     elseExpression->visit();
    return expression->visit();
}
} // namespace CulLang

// namespace CulLang