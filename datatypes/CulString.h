#pragma once
#include "Object.h"

namespace CulLang {
class String : public Object {
  public:
    String(const std::string &str) : val(str) { type = culStr; }
    virtual void *getVal() override { return &val; }
    virtual std::string asAStr() override { return val; }

    virtual Ref<Object> __add__(Ref<Object> a) override {
        if (a->type == culStr) {
            return std::make_shared<String>(val +
                                            (*(std::string *)a->getVal()));
        }
        return Object::NONE->__add__(a);
    }

    virtual Ref<Object> __mul__(Ref<Object> a) override {
        if (a->type == culInt) {
            std::string out = "";
            for (int i = 0; i < *(int *)a->getVal(); i++)
                out += val;
            return std::make_shared<String>(out);
        }
        return Object::NONE->__mul__(a);
    }

    virtual std::string getInC() override { return '"'+asAStr()+'"'; }

  private:
    std::string val;
};
} // namespace CulLang