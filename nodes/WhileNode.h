#pragma once

#include "Node.h"
namespace CulLang {
class WhileNode : public Node {
  public:
    const Ref<Node> condition = nullptr;
    const Ref<Node> expression = nullptr;

    WhileNode(const Ref<Node> &condition, const Ref<Node> &expression);
    virtual ~WhileNode() override;

    virtual std::string getInStr() override;
    NodeType getType() override  { return WhileblockNode; }
    virtual std::array<Position, 2> getPos() override;

    virtual Ref<Object> visit() override;
};
WhileNode::WhileNode(const Ref<Node> &condition, const Ref<Node> &expression)
    : condition(condition), expression(expression){}

WhileNode::~WhileNode() {}

std::string WhileNode::getInStr() {
    auto out =
        "while " + condition->getInStr() + " : " + expression->getInStr();
    return out;
};

std::array<Position, 2> WhileNode::getPos() { return condition->getPos(); }

Ref<Object> WhileNode::visit() {

    while (*(bool *)condition->visit()->getVal()) {
        expression->visit();
    }
    return Object::NONE;
}
} // namespace CulLang