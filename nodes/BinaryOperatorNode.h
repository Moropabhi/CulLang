#pragma once
#include "../datatypes/Bool.h"
#include "Node.h"
namespace CulLang {
class BinaryOperatorNode : public Node {
 public:
  Ref<Node> left;
  Ref<Node> right;

  BinaryOperatorNode(const Ref<Node>& left,
                     const Token* op,
                     const Ref<Node>& right);
  virtual ~BinaryOperatorNode() override;

  virtual std::string getInStr() override;
  NodeType getType() override;
  virtual std::array<Position, 2> getPos() override;

  virtual Ref<Object> visit() override;
  Ref<Object> callOperation(const Token* val,
                            const Ref<Object>& L,
                            const Ref<Object>& R);
};

BinaryOperatorNode::BinaryOperatorNode(const Ref<Node>& left,
                                       const Token* op,
                                       const Ref<Node>& right)
    : left(left), Node(op), right(right) {
  type = BinaryNode;
}

BinaryOperatorNode::~BinaryOperatorNode() {}

std::string BinaryOperatorNode::getInStr() {
  return " ( " + left->getInStr() + " " + Node::getInStr() + " " +
         right->getInStr() + " ) ";
};

NodeType BinaryOperatorNode::getType() {
  return BinaryNode;
}

std::array<Position, 2> BinaryOperatorNode::getPos() {
  return {left->getPos()[0], right->getPos()[1]};
}

Ref<Object> BinaryOperatorNode::visit() {
  auto L = left->visit();
  auto R = right->visit();
  return callOperation(value, L, R);
}

Ref<Object> BinaryOperatorNode::callOperation(const Token* val,
                                              const Ref<Object>& L,
                                              const Ref<Object>& R) {
  Ref<Object> res = Object::NONE;
  bool val_bool;
  switch (val->getType()) {
    case culPlus:
      res = L->__add__(R);
      break;
    case culMinus:
      res = L->__sub__(R);
      break;
    case culMul:
      res = L->__mul__(R);
      break;
    case culDiv:
      res = L->__div__(R);
      break;
    case culPower:
      res = L->__pow__(R);
      break;
    case culMod:
      res = L->__mod__(R);
      break;
    case culIsEqual:
      val_bool = L->__eq__(R);
      break;
    case culNotEqual:
      val_bool = L->__neq__(R);
      break;
    case culGreaterEqual:
      val_bool = L->__geq__(R);
      break;
    case culLesserEqual:
      val_bool = L->__leq__(R);
      break;
    case culGreater:
      val_bool = L->__gt__(R);
      break;
    case culLesser:
      val_bool = L->__lt__(R);
      break;
    case culKeyword:
      switch (
          std::find(CulKeywordStr.begin(), CulKeywordStr.end(), val->getVal()) -
          CulKeywordStr.begin()) {
        case culAnd:
          val_bool = L->__and__(R);
          break;
        case culOr:
          val_bool = L->__or__(R);
          break;
        default:
          ErrorHandler::raiseError({ErrorType::FeatureNotImplementedYet,
                                    getPos(),
                                    "This (keyword) operation is not "
                                    "implemented yet from BinaryOperatorNode"});
          return Object::NONE;
      }
      break;
    default:
      ErrorHandler::raiseError(
          {ErrorType::FeatureNotImplementedYet, getPos(),
           "This operation is not implemented yet from BinaryOperatorNode"});
      return Object::NONE;
  }
  
  if (ErrorHandler::anyStackErrors()) {
    auto& errs = ErrorHandler::getStack();
    for (auto& i : errs)
      i.setPos(getPos());
    ErrorHandler::raiseStackAll();
    return Object::NONE;
  }

  return res == Object::NONE ? std::make_shared<Bool>(val_bool) : res;
}

}  // namespace CulLang