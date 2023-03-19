#pragma once
#include "Object.h"

namespace CulLang {
class Bool : public Object {
  public:
    Bool() { type = culBool; }
    Bool(bool a) : val(a) { type = culBool; }
    Bool(const std::string &a) : val(a == "true" ? true : false) {
        type = culBool;
    }
    virtual void *getVal() override { return &val; }
    virtual std::string asAStr() override { return val ? "true" : "false"; }

    virtual bool __eq__(Ref<Object> val2) {
        if (val2->type == culBool)
            return val == *(bool *)val2->getVal();
        return Object::NONE->__eq__(val2);
    }
    virtual bool __neq__(Ref<Object> val2) {
        if (val2->type == culBool)
            return val != *(bool *)val2->getVal();
        return Object::NONE->__neq__(val2);
    }

    virtual bool __and__(Ref<Object> val2) {
        if (val2->type == culBool)
            return val && *(bool *)val2->getVal();
        return Object::NONE->__and__(val2);
    }
    virtual bool __or__(Ref<Object> val2) {
        if (val2->type == culBool)
            return val && *(bool *)val2->getVal();
        return Object::NONE->__or__(val2);
    }
    virtual void __not__() { val = !val; }

    virtual std::string getInC() override { return val ? "1" : "0"; }

  private:
    bool val;
};
} // namespace CulLang