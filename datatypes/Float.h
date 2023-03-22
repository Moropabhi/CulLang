#pragma once
#include "Object.h"
#include <cmath>


namespace CulLang {
class Float : public Object {
  public:
    Float() { type = culFloat; }

    Float(FLOAT a) : val(a) { type = culFloat; }

    Float(const std::string &a) {
        type = culFloat;
        sscanf(a.c_str(), "%f", &val);
    }

    virtual void *getVal() override { return &val; }

    virtual std::string asAStr() override { return std::to_string(val); }

    virtual void __plus__() override {}
    virtual void __minus__() override { val = -val; }

    virtual Ref<Object> __add__(Ref<Object> a) override {
        if (a->type == culInt) {
            return std::make_shared<Float>(val + *(INTEGER *)a->getVal());
        }
        if (a->type == culFloat) {
            return std::make_shared<Float>(val + *(FLOAT *)a->getVal());
        }
        return Object::NONE;
    }
    virtual Ref<Object> __sub__(Ref<Object> a) override {
        if (a->type == culInt) {
            return std::make_shared<Float>(val - *(INTEGER *)a->getVal());
        }
        if (a->type == culFloat) {
            return std::make_shared<Float>(val - *(FLOAT *)a->getVal());
        }
        return Object::NONE;
    }
    virtual Ref<Object> __mul__(Ref<Object> a) override {
        if (a->type == culInt) {
            return std::make_shared<Float>(val * *(INTEGER *)a->getVal());
        }
        if (a->type == culFloat) {
            return std::make_shared<Float>(val * *(FLOAT *)a->getVal());
        }
        return Object::NONE;
    }
    virtual Ref<Object> __div__(Ref<Object> a) override {
        if (a->type == culInt) {
            const INTEGER b = *(INTEGER *)a->getVal();
            if (!b) {
                ErrorHandler::stackError({ZeroDivision, "Dividing by zero"});
                return Object::NONE;
            }
            return std::make_shared<Float>(val / b);
        }
        if (a->type == culFloat) {
            const FLOAT b = *(FLOAT *)a->getVal();
            if (!b) {
                ErrorHandler::stackError({ZeroDivision, "Dividing by zero"});
                return Object::NONE;
            }
            return std::make_shared<Float>(val / b);
        }
        return Object::NONE;
    }
    virtual Ref<Object> __pow__(Ref<Object> a) override {
        if (a->type == culInt) {
            return std::make_shared<Float>(
                std::pow(val, *(INTEGER *)a->getVal()));
        }
        if (a->type == culFloat) {
            return std::make_shared<Float>(
                std::pow(val, *(FLOAT *)a->getVal()));
        }
        return Object::NONE;
    }

    virtual void __iadd__(Ref<Object> a) override {
        if (a->type == culInt) {
            val += *(INTEGER *)a->getVal();
        }
        if (a->type == culFloat) {
            val += *(FLOAT *)a->getVal();
        }
    }
    virtual void __isub__(Ref<Object> a) override {
        if (a->type == culInt) {
            val -= *(INTEGER *)a->getVal();
        }
        if (a->type == culFloat) {
            val -= *(FLOAT *)a->getVal();
        }
    }
    virtual void __imul__(Ref<Object> a) override {
        if (a->type == culInt) {
            val *= *(INTEGER *)a->getVal();
        }
        if (a->type == culFloat) {
            val *= *(FLOAT *)a->getVal();
        }
    }
    virtual void __idiv__(Ref<Object> a) override {
        if (a->type == culInt) {
            const auto b = *(INTEGER *)a->getVal();
            if (!b)
                return ErrorHandler::stackError(
                    {ZeroDivision, "Dividing by zero"});
            val += b;
        }
        if (a->type == culFloat) {
            const auto b = *(FLOAT *)a->getVal();
            if (!b)
                return ErrorHandler::stackError(
                    {ZeroDivision, "Dividing by zero"});
            val += b;
        }
    }
    virtual void __ipow__(Ref<Object> a) override {
        if (a->type == culInt) {
            val = std::pow(val, *(INTEGER *)a->getVal());
        }
        if (a->type == culFloat) {
            val += std::pow(val, *(FLOAT *)a->getVal());
        }
    }

      virtual bool __eq__(Ref<Object> val2) {
    if(val2->type==culInt)
        return val == *(INTEGER*)val2->getVal();
    if(val2->type==culFloat)
        return val == *(FLOAT*)val2->getVal();
    return Object::NONE->__eq__(val2);
  }
  virtual bool __neq__(Ref<Object> val2) {
    if(val2->type==culInt)
        return val != *(INTEGER*)val2->getVal();
    if(val2->type==culFloat)
        return val != *(FLOAT*)val2->getVal();
    return Object::NONE->__neq__(val2);
  }
  virtual bool __gt__(Ref<Object> val2) {
    if(val2->type==culInt)
        return val > *(INTEGER*)val2->getVal();
    if(val2->type==culFloat)
        return val > *(FLOAT*)val2->getVal();
    return Object::NONE->__gt__(val2);
  }
  virtual bool __lt__(Ref<Object> val2) {
        if(val2->type==culInt)
        return val < *(INTEGER*)val2->getVal();
    if(val2->type==culFloat)
        return val < *(FLOAT*)val2->getVal();
    return Object::NONE->__lt__(val2);
  }
  virtual bool __geq__(Ref<Object> val2) {
        if(val2->type==culInt)
        return val >= *(INTEGER*)val2->getVal();
    if(val2->type==culFloat)
        return val >= *(FLOAT*)val2->getVal();
    return Object::NONE->__geq__(val2);
  }
  virtual bool __leq__(Ref<Object> val2) {
        if(val2->type==culInt)
        return val <= *(INTEGER*)val2->getVal();
    if(val2->type==culFloat)
        return val <= *(FLOAT*)val2->getVal();
    return Object::NONE->__leq__(val2);
  }


    virtual std::string getInC() override
  {
    return asAStr();
  }

  private:
    FLOAT val;
};
} // namespace CulLang