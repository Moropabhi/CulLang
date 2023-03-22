#pragma once

#include "Node.h"

namespace CulLang {
class IfElifNode : public Node {
  public:
    struct ElifCode {
        const Ref<Node> condition = nullptr;
        const Ref<Node> expression = nullptr;
    };

    std::vector<ElifCode> ifs;
    const Ref<Node> elseExpression = nullptr;

    IfElifNode(const std::vector<ElifCode> &ifs,
               const Ref<Node> &elseexpr = nullptr);
    IfElifNode(std::vector<ElifCode> &&ifs,
               const Ref<Node> &elseexpr = nullptr);
    virtual ~IfElifNode() override;

    virtual std::string getInStr() override;
    NodeType getType() override  { return IfblockNode; }
    virtual std::array<Position, 2> getPos() override;

    virtual Ref<Object> visit() override;
};
} // namespace CulLang
namespace CulLang {

IfElifNode::IfElifNode(const std::vector<ElifCode> &ifs,
                       const Ref<Node> &elseexpr)
    :  ifs(ifs),
      elseExpression(elseexpr) {}
IfElifNode::IfElifNode(std::vector<ElifCode> &&ifs, const Ref<Node> &elseexpr)
    :  ifs(ifs),
      elseExpression(elseexpr) {}

IfElifNode::~IfElifNode() {}

std::string IfElifNode::getInStr() {
    std::string out;

    for (auto &i : ifs)   
    {
        static bool is_if = true;
        out+=(is_if?"if ":"\nelif ") + i.condition->getInStr() + " : " +
               i.expression->getInStr();

    } 

    if (elseExpression) {
        out += "\nelse : " + elseExpression->getInStr();
    }
    return out;
};

std::array<Position, 2> IfElifNode::getPos() {
    return {ifs[0].condition->getPos()[0], ifs[0].expression->getPos()[1]};
}

Ref<Object> IfElifNode::visit() {

    for (auto &if_ : ifs) {
        Ref<Object> condition = if_.condition->visit();
        if (*(bool *)condition->getVal()) {
            if_.expression->visit();
            return Object::NONE;
        }
    }

    if (elseExpression)
        elseExpression->visit();
    return Object::NONE;
}

} // namespace CulLang