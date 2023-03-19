#pragma once
#include "Error.h"

namespace CulLang {


class ErrorHandler {
  public:

    static void raiseError(const Error &error) {
        error.raise();
        isThereAnyErrors = true;
    }

    static bool anyErrors() { return isThereAnyErrors; }
    static void clear() { isThereAnyErrors = false; }
    static void stackError(const Error &error) {getStack().push_back(error); }

    static Error &getFromStack(int Index) { return getStack()[Index]; }
    static void raiseStackAll() {
        for (auto &err : getStack())
            raiseError(err);
        getStack().clear();
    }
    static void raiseFromStack(int index) {
        auto &errs = getStack();
        raiseError(errs[index]);
        errs.erase(errs.begin() + index);
    }
    static std::vector<Error> &getStack() {
        static std::vector<Error> errs;
        return errs;
    }
    static bool anyStackErrors() { return bool(getStack().size()); }


  private:
    static bool isThereAnyErrors;
};
bool ErrorHandler::isThereAnyErrors = false;
} // namespace CulLang