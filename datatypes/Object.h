#pragma once

#include "../debug/ErrorHandler.h"

namespace CulLang {
struct Object {
  Object() = default;

  virtual std::string asAStr();
  virtual void* getVal() { return nullptr; }
  virtual std::string getInC() {return "";}

  virtual ~Object() = default;

  virtual void __plus__() {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '+'(.__plus__) is not defined for these operands"});
  }
  virtual void __minus__() {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '-'(.__minus__) is not defined for these operands"});
  }
  virtual void __increment__() {
    ErrorHandler::stackError({ErrorType::InvalidOperation,
                              "This operation '++'(.__increment__) is not "
                              "defined for these operands"});
  }
  virtual void __decrement__() {
    ErrorHandler::stackError({ErrorType::InvalidOperation,
                              "This operation '--'(.__decrement__) is not "
                              "defined for these operands"});
  }

  // Binary Operation

  virtual Ref<Object> __add__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '+'(.__add__) is not defined for these operands"});
    return Object::NONE;
  }
  virtual Ref<Object> __sub__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '-'(.__sub__) is not defined for these operands"});
    return Object::NONE;
  }
  virtual Ref<Object> __mul__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '*'(.__mul__) is not defined for these operands"});
    return Object::NONE;
  }
  virtual Ref<Object> __div__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '/'(.__div__) is not defined for these operands"});
    return Object::NONE;
  }
  virtual Ref<Object> __pow__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '**'(.__pow__) is not defined for these operands"});
    return Object::NONE;
  }
  virtual Ref<Object> __mod__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '%'(.__mod__) is not defined for these operands"});
    return Object::NONE;
  }

  // Augumented Operator

  virtual void __iadd__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '+'(.__add__) is not defined for these operands"});
  }
  virtual void __isub__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '-'(.__sub__) is not defined for these operands"});
  }
  virtual void __imul__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '*'(.__mul__) is not defined for these operands"});
  }
  virtual void __idiv__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '/'(.__div__) is not defined for these operands"});
  }
  virtual void __ipow__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '**'(.__pow__) is not defined for these operands"});
  }
  virtual void __imod__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '%'(.__mod__) is not defined for these operands"});
  }

  // Conditional Operator

  virtual bool __eq__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '=='(.__eq__) is not defined for these operands"});
    return false;
  }
  virtual bool __neq__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '!='(.__neq__) is not defined for these operands"});
    return false;
  }
  virtual bool __gt__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '>'(.__gt__) is not defined for these operands"});
    return false;
  }
  virtual bool __lt__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '<'(.__lt__) is not defined for these operands"});
    return false;
  }
  virtual bool __geq__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '>='(.__geq__) is not defined for these operands"});
    return false;
  }
  virtual bool __leq__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '<='(.__leq__) is not defined for these operands"});
    return false;
  }

  // Logical Operator

  virtual bool __and__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '<='(.__and__) is not defined for these operands"});
    return false;
  }
  virtual bool __or__(Ref<Object> val2) {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '<='(.__or__) is not defined for these operands"});
    return false;
  }
  virtual void __not__() {
    ErrorHandler::stackError(
        {ErrorType::InvalidOperation,
         "This operation '<='(.__not__) is not defined for these operands"});
  }

 public:
  Datatypes type = (Datatypes)culNone;
  static Ref<Object> NONE;
};
Ref<Object> Object::NONE = std::make_shared<Object>();
using None = Object;

std::string Object::asAStr() {
  return "None";
}
}  // namespace CulLang