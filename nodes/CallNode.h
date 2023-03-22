#pragma once
#include "../Utilities.h"

#include "Node.h"
namespace CulLang {
class CallNode : public Node {
  public:
    CallNode(const Token *name);
    virtual ~CallNode() override;

    virtual std::string getInStr() override;
    NodeType getType() override  { return CallableNode; }
    virtual std::array<Position, 2> getPos() override;

    virtual Ref<Object> visit() override;
  private:
  Token name_tok;
};

CallNode::CallNode(const Token *name) : name_tok(std::move(*name)) {}

CallNode::~CallNode() {}

std::string CallNode::getInStr() {
    auto out = name_tok.getVal() + "()";
    return out;
};

std::array<Position, 2> CallNode::getPos() { return name_tok.getPos(); }

Ref<Object> CallNode::visit() { return Object::NONE; }
} // namespace CulLang