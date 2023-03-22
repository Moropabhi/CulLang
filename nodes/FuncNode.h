#pragma once
#include "../Utilities.h"
#include "Node.h"
namespace CulLang {
class FuncNode : public Node {
  public:
    const Ref<Node> expression = nullptr;

    FuncNode(const Token *name, const Ref<Node> &expression);
    virtual ~FuncNode() override;

    virtual std::string getInStr() override;
    NodeType getType() override  { return FuncblockNode; }
    virtual std::array<Position, 2> getPos() override;

    virtual Ref<Object> visit() override;

  private:
    Token name_tok;
};
} // namespace CulLang
namespace CulLang {

FuncNode::FuncNode(const Token *name, const Ref<Node> &expression)
    : expression(expression), name_tok(std::move(*name)) {}

FuncNode::~FuncNode() {}

std::string FuncNode::getInStr() {
    auto out = "while "
               " : " +
               expression->getInStr();
    return out;
};

std::array<Position, 2> FuncNode::getPos() { return name_tok.getPos(); }

Ref<Object> FuncNode::visit() {
    return expression->visit();
}
} // namespace CulLang