#pragma once

#include "../Utilities.h"
#include "Node.h"
namespace CulLang {
class ForNode : public Node {
  public:
    const Ref<Node> initial = nullptr;
    const Ref<Node> condition = nullptr;
    const Ref<Node> increment = nullptr;
    const Ref<Node> expression = nullptr;

    ForNode(const Ref<Node> &initial, const Ref<Node> &condition,
            const Ref<Node> &increment, const Ref<Node> &expression);
    virtual ~ForNode() override;

    virtual std::string getInStr() override;
    NodeType getType() override  { return ForblockNode; }
    virtual std::array<Position, 2> getPos() override;

    virtual Ref<Object> visit() override;
};
ForNode::ForNode(const Ref<Node> &initial, const Ref<Node> &condition,
                 const Ref<Node> &increment, const Ref<Node> &expression)
    : initial(initial), condition(condition), increment(increment),
      expression(expression) {}

ForNode::~ForNode() {}

std::string ForNode::getInStr() {
    auto out = "for " + initial->getInStr() + " \\ " + condition->getInStr() +
               " \\ " + increment->getInStr() + " : " + expression->getInStr();
    return out;
};

std::array<Position, 2> ForNode::getPos() {
    return {initial->getPos()[0], increment->getPos()[1]};
}

Ref<Object> ForNode::visit() {

    for (initial->visit(); *(bool *)(condition->visit()->getVal());
         increment->visit()) {
        expression->visit();
    }
    return Object::NONE;
}
} // namespace CulLang