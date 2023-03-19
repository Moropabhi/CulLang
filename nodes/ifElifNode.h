#pragma once

#include "Node.h"


namespace CulLang {
class IfElifNode : public Node {
  public:
    const Ref<Node> condition = nullptr;
    const Ref<Node> expression = nullptr;

    struct ElifCode {
        const Ref<Node> condition = nullptr;
        const Ref<Node> expression = nullptr;
    };

    std::vector<ElifCode> elifs;
    const Ref<Node> elseExpression = nullptr;

    IfElifNode(const Ref<Node> &condition, const Ref<Node> &expression,
               const std::vector<ElifCode> &elifs,
               const Ref<Node> &elseexpr = nullptr);
    IfElifNode(const Ref<Node> &condition, const Ref<Node> &expression,
               std::vector<ElifCode> &&elifs,
               const Ref<Node> &elseexpr = nullptr);
    virtual ~IfElifNode() override;

    virtual std::string getInStr() override;
    NodeType getType() override;
    virtual std::array<Position, 2> getPos() override;

    virtual Ref<Object> visit() override;
};
} // namespace CulLang
namespace CulLang {

IfElifNode::IfElifNode(const Ref<Node> &condition, const Ref<Node> &expression,
                       const std::vector<ElifCode> &elifs,
                       const Ref<Node> &elseexpr)
    : condition(condition), expression(expression), elifs(elifs),
      elseExpression(elseexpr), Node(nullptr) {
    type = IfblockNode;
}
IfElifNode::IfElifNode(const Ref<Node> &condition, const Ref<Node> &expression,
                       std::vector<ElifCode> &&elifs,
                       const Ref<Node> &elseexpr)
    : condition(condition), expression(expression), elifs(elifs), elseExpression(elseexpr),
      Node(nullptr) {
    type = IfblockNode;
}

IfElifNode::~IfElifNode() {}

std::string IfElifNode::getInStr() {
    auto out = "if " + condition->getInStr() + " : " + expression->getInStr();

    for ( auto& i : elifs)
        out+= "\nelif"+i.condition->getInStr()+" : "+i.expression->getInStr();

    if(elseExpression)
    {
        out += "\nelse : " + elseExpression->getInStr();
    }
    return out;
};

NodeType IfElifNode::getType() { return IfblockNode; }

std::array<Position, 2> IfElifNode::getPos() {
    return {condition->getPos()[0], expression->getPos()[1]};
}

Ref<Object> IfElifNode::visit() {
    auto cond = condition->visit();
    if (*(bool *)cond->getVal()) {
        expression->visit();
        return Object::NONE;
    }

    for (auto &elif : elifs) {
        auto cond = elif.condition->visit();
        if (*(bool *)cond->getVal()) {
            elif.expression->visit();
            return Object::NONE;
        }
    }

    if (elseExpression)
        elseExpression->visit();
    return Object::NONE;
}

} // namespace CulLang