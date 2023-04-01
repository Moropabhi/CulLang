#include "Node.h"
namespace CulLang {
class LoopNode : public Node {
  public:
    const Ref<Node> expression = nullptr;

    LoopNode(const Ref<Node> &expression);
    virtual ~LoopNode() override;

    virtual std::string getInStr() override;
    NodeType getType() override { return LoopblockNode; }
    virtual std::array<Position, 2> getPos() override;

    virtual Ref<Object> visit() override;
};
LoopNode::LoopNode(const Ref<Node> &expression)
    : expression(expression) {}

LoopNode::~LoopNode() {}

std::string LoopNode::getInStr() {
    auto out =
        "loop : " + expression->getInStr();
    return out;
};

std::array<Position, 2> LoopNode::getPos() { return expression->getPos(); }

Ref<Object> LoopNode::visit() {

    while (!BreakNode::shouldBreak) {
        expression->visit();
    }
    BreakNode::shouldBreak = false;
    return Object::NONE;
}
} // namespace CulLang