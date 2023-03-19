#pragma once

#include "Node.h"
namespace CulLang {
class BlockNode : public Node {
  public:

    BlockNode(std::vector<Ref<Node>> &&expression);
    virtual ~BlockNode() override;

    virtual std::string getInStr() override;
    NodeType getType() override;
    virtual std::array<Position, 2> getPos() override;

    virtual Ref<Object> visit() override;

    std::vector<Ref<Node>> expressions;
};

BlockNode::BlockNode(std::vector<Ref<Node>> &&expressions)
    :expressions(expressions){
    type = blockNode;
}

BlockNode::~BlockNode() {}

std::string BlockNode::getInStr() {
    std::string out ="{ ";
    for(auto& i: expressions )
        out+=i->getInStr()+"\n";
    out+=" }";
    // if(elseExpression)
    // {
    //     out += " else : " + elseExpression->getInStr();
    // }
    return out;
};

NodeType BlockNode::getType() { return blockNode; }

std::array<Position, 2> BlockNode::getPos() { return {expressions[0]->getPos()[0],expressions.back()->getPos()[1]}; }

Ref<Object> BlockNode::visit() {

    for (auto& i: expressions ) {
        i->visit();
    }
    // if (elseExpression)
    //     elseExpression->visit();
    return Object::NONE;
}
} // namespace CulLang