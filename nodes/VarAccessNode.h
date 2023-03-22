#pragma once
#include "Node.h"
namespace CulLang {

class VarAccessNode : public Node {
  public:
    VarAccessNode(const Token *v) : var_tok(std::move(*v)) {}

    virtual Ref<Object> visit() override;

    virtual NodeType getType() override { return VarAccessingNode; }
    virtual std::array<Position, 2> getPos() override {
        return var_tok.getPos();
    }

    virtual std::string getInStr() override { return var_tok.getVal(); }

  private:
    Token var_tok;
};
Ref<Object> VarAccessNode::visit() {
    return SymbolTable::getGlobal().getValue(var_tok);
}
} // namespace CulLang
