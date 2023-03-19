#pragma once

#include "Node.h"
namespace CulLang {
class IfNode : public Node {
  public:
    const Ref<Node> condition = nullptr;
    const Ref<Node> expression = nullptr;
    const Ref<Node> elseExpression = nullptr;

    IfNode(const Ref<Node> &condition, const Ref<Node> &expression,
           const Ref<Node> &elseexpr);
    IfNode(const Ref<Node> &condition, const Ref<Node> &expression);
    virtual ~IfNode() override;

    virtual std::string getInStr() override;
    NodeType getType() override;
    virtual std::array<Position, 2> getPos() override;

    virtual Ref<Object> visit() override;
};

IfNode::IfNode(const Ref<Node> &condition, const Ref<Node> &expression,
               const Ref<Node> &elseexpr)
    : condition(condition), expression(expression), elseExpression(elseexpr),
      Node(nullptr) {
    type = IfblockNode;
}
IfNode::IfNode(const Ref<Node> &condition, const Ref<Node> &expression)
    : condition(condition), expression(expression), Node(nullptr) {
    type = IfblockNode;
}

IfNode::~IfNode() {}

std::string IfNode::getInStr() {
    auto out = "if " + condition->getInStr() + " : " + expression->getInStr();
    if(elseExpression)
    {
        out += " else : " + elseExpression->getInStr();
    }
    return out;
};

NodeType IfNode::getType() { return IfblockNode; }

std::array<Position, 2> IfNode::getPos() {
    return {condition->getPos()[0], expression->getPos()[1]};
}

Ref<Object> IfNode::visit() {
    auto cond = condition->visit();
    if (*(bool *)cond->getVal()) {
        expression->visit();expression->visit();
        return Object::NONE;
    }
    if (elseExpression)
        elseExpression->visit();
    return Object::NONE;
}
} // namespace CulLang