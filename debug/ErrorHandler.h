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
    static void stackError(const Error &error) {
#if !THROW_ERROR
        getStack().push_back(error);
#endif
    }

    static Error &getFromStack(int Index) {
#if !THROW_ERROR
        return getStack()[Index];
#endif
    }
    static void raiseStackAll() {
#if !THROW_ERROR
        for (auto &err : getStack())
            raiseError(err);
        getStack().clear();
#endif
    }
    static void raiseFromStack(int index) {
#if !THROW_ERROR
        auto &errs = getStack();
        raiseError(errs[index]);
        errs.erase(errs.begin() + index);
#endif
    }
    static std::vector<Error> &getStack() {
        static std::vector<Error> errs;
        return errs;
    }
    static bool anyStackErrors() {
#if !THROW_ERROR
        return bool(getStack().size());
#endif
    }

  private:
    static bool isThereAnyErrors;
};
bool ErrorHandler::isThereAnyErrors = false;
} // namespace CulLang