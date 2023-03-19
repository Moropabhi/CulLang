#pragma once
#include "../Utilities.h"

#include "Node.h"
namespace CulLang {
class CallNode : public Node {
  public:
    CallNode(const Token *name);
    virtual ~CallNode() override;

    virtual std::string getInStr() override;
    NodeType getType() override;
    virtual std::array<Position, 2> getPos() override;

    virtual Ref<Object> visit() override;
};

CallNode::CallNode(const Token *name) : Node(name) { type = CallableNode; }

CallNode::~CallNode() {}

std::string CallNode::getInStr() {
    auto out = value->getVal() + "()";
    return out;
};

NodeType CallNode::getType() { return CallableNode; }

std::array<Position, 2> CallNode::getPos() { return value->getPos(); }

Ref<Object> CallNode::visit() { return Object::NONE; }
} // namespace CulLang