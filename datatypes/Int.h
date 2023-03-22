#pragma once
#include "Object.h"
#include <cmath>
#include "Float.h"

namespace CulLang {
class Int : public Object {
 public:

  using valuetype = int64_t;

  Int() { type = culInt; }
  Int(INTEGER a) : val(a) { type = culInt; }
  Int(const std::string& a) : val(stoi(a)) { type = culInt; }
  virtual void* getVal() override { return &val; }
  virtual std::string asAStr() override { return std::to_string(val); }
  virtual void __plus__() override {}
  virtual void __minus__() override { val = -val; }
  virtual void __increment__() { val += 1; }
  virtual void __decrement__() { val--; }

  virtual Ref<Object> __add__(Ref<Object> a) override {
    if (a->type == culInt) {
      return std::make_shared<Int>(val + *(INTEGER*)a->getVal());
    }
    if (a->type == culFloat) {
      return std::make_shared<Float>(val + *(FLOAT*)a->getVal());
    }
    return Object::NONE->__add__(a);
  }
  virtual Ref<Object> __sub__(Ref<Object> a) override {
    if (a->type == culInt) {
      return std::make_shared<Int>(val - *(INTEGER*)a->getVal());
    }
    if (a->type == culFloat) {
      return std::make_shared<Float>(val - *(FLOAT*)a->getVal());
    }
    return Object::NONE->__sub__(a);
  }
  virtual Ref<Object> __mul__(Ref<Object> a) override {
    if (a->type == culInt) {
      return std::make_shared<Int>(val * *(INTEGER*)a->getVal());
    }
    if (a->type == culFloat) {
      return std::make_shared<Float>(val * *(FLOAT*)a->getVal());
    }
    return Object::NONE->__mul__(a);
  }
  virtual Ref<Object> __div__(Ref<Object> a) override {
    if (a->type == culInt) {
      const INTEGER b = *(INTEGER*)a->getVal();
      if (!b) {
        ErrorHandler::stackError({ZeroDivision, "Dividing by zero"});
        return Object::NONE;
      }
      return std::make_shared<Int>(val / b);
    }
    if (a->type == culFloat) {
      const FLOAT b = *(FLOAT*)a->getVal();
      if (!b) {
        ErrorHandler::stackError({ZeroDivision, "Dividing by zero"});
        return Object::NONE;
      }
      return std::make_shared<Float>(val / b);
    }
    return Object::NONE->__div__(a);
  }
  virtual Ref<Object> __pow__(Ref<Object> a) override {
    if (a->type == culInt) {
      INTEGER i = val;
      INTEGER num = *(INTEGER*)a->getVal();
      for (int n = 1; n < num; n++)
        i *= val;

      return std::make_shared<Int>(i);
    }
    if (a->type == culFloat) {
      return std::make_shared<Float>(std::pow(val, *(FLOAT*)a->getVal()));
    }
    return Object::NONE->__pow__(a);
  }
  virtual Ref<Object> __mod__(Ref<Object> a) override {
    if (a->type == culInt) {
      return std::make_shared<Int>(val % *(INTEGER*)a->getVal());
    }
    return Object::NONE->__mod__(a);
  }

  virtual void __iadd__(Ref<Object> a) override {
    if (a->type == culInt) {
      val += *(INTEGER*)a->getVal();
      return;
    }
    return Object::NONE->__iadd__(a);
  }
  virtual void __isub__(Ref<Object> a) override {
    if (a->type == culInt) {
      val -= *(INTEGER*)a->getVal();
      return;
    }
    return Object::NONE->__isub__(a);
  }
  virtual void __imul__(Ref<Object> a) override {
    if (a->type == culInt) {
      val *= *(INTEGER*)a->getVal();
      return;
    }
    return Object::NONE->__imul__(a);
  }
  virtual void __idiv__(Ref<Object> a) override {
    if (a->type == culInt) {
      const INTEGER b = *(INTEGER*)a->getVal();
      if (!b)
        return ErrorHandler::stackError({ZeroDivision, "Dividing by zero"});
      val /= b;
      return;
    }
    return Object::NONE->__idiv__(a);
  }
  virtual void __ipow__(Ref<Object> a) override {
    if (a->type == culInt) {
      INTEGER i = val;
      INTEGER num = *(INTEGER*)a->getVal();
      for (int n = 1; n < num; n++)
        i *= val;
      val = i;
      return;
    }
    return Object::NONE->__ipow__(a);
  }
  virtual void __imod__(Ref<Object> a) override {
    if (a->type == culInt) {
      val %= *(INTEGER*)a->getVal();
      return;
    }
    return Object::NONE->__imod__(a);
  }

  virtual bool __eq__(Ref<Object> val2) {
    if(val2->type==culInt)
        return val == *(INTEGER*)val2->getVal();
    return Object::NONE->__eq__(val2);
  }
  virtual bool __neq__(Ref<Object> val2) {
    if(val2->type==culInt)
        return val != *(INTEGER*)val2->getVal();
    return Object::NONE->__neq__(val2);
  }
  virtual bool __gt__(Ref<Object> val2) {
    if(val2->type==culInt)
        return val > *(INTEGER*)val2->getVal();
    return Object::NONE->__gt__(val2);
  }
  virtual bool __lt__(Ref<Object> val2) {
        if(val2->type==culInt)
        return val < *(INTEGER*)val2->getVal();
    return Object::NONE->__lt__(val2);
  }
  virtual bool __geq__(Ref<Object> val2) {
        if(val2->type==culInt)
        return val >= *(INTEGER*)val2->getVal();
    return Object::NONE->__geq__(val2);
  }
  virtual bool __leq__(Ref<Object> val2) {
        if(val2->type==culInt)
        return val <= *(INTEGER*)val2->getVal();
    return Object::NONE->__leq__(val2);
  }

  virtual std::string getInC() override
  {
    return asAStr();
  }

 private:
  INTEGER val;
};
}  // namespace CulLang
