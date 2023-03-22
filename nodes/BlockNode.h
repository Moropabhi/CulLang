#pragma once

#include "Node.h"
namespace CulLang {
class BlockNode : public Node {
  public:
    BlockNode(std::vector<Ref<Node>> &&expression);
    virtual ~BlockNode() override;

    virtual std::string getInStr() override;
    NodeType getType() override { return blockNode; }
    virtual std::array<Position, 2> getPos() override {
        return {expressions[0]->getPos()[0], expressions.back()->getPos()[1]};
    }

    virtual Ref<Object> visit() override;

    std::vector<Ref<Node>> expressions;
};

BlockNode::BlockNode(std::vector<Ref<Node>> &&expressions)
    : expressions(expressions) {}

BlockNode::~BlockNode() {}

std::string BlockNode::getInStr() {
    std::string out = "{ ";
    for (auto &i : expressions)
        out += i->getInStr() + "\n";
    out += " }";
    return out;
};

Ref<Object> BlockNode::visit() {

    for (auto &i : expressions) {
        i->visit();
    }
    return Object::NONE;
}
} // namespace CulLang