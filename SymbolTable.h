#pragma once
#include "Utilities.h"
#include "datatypes/Object.h"
#include "nodes/Node.h"

namespace CulLang {
class SymbolTable {
  public:
    void addVariable(const Token &value, Ref<Object> o);
    Ref<Object> getValue(const Token &value);
    void setValue(const Token &value, Ref<Object> o);
    void deleteVariable(const Token &value);

    void addFunc(const Token &value, Ref<Node> o);
    Ref<Node> getFunc(const Token &value);
    void setFunc(const Token &value, Ref<Node> o);
    void deleteFunc(const Token &value);

    bool isThereVariable(const Token &value);
    bool isThereFunc(const Token &value);

    static SymbolTable &getGlobal();
    void clear();

  private:
    Dict<std::string, Ref<Object>> vartable;
    Dict<std::string, Ref<Node>> funcTable;
    static SymbolTable* currentTable;
};

SymbolTable* SymbolTable::currentTable = &SymbolTable::getGlobal();

void SymbolTable::addVariable(const Token &value, Ref<Object> o) {
    if (isThereVariable(value))
        ErrorHandler::raiseError({ErrorType::NotDefined, value.getPos()[0],
                                  value.getPos()[1],
                                  "Identifier already defined"});
    vartable[value.getVal()] = o;
}
Ref<Object> SymbolTable::getValue(const Token &value) {
    if (isThereVariable(value))
        return vartable.at(value.getVal());
    if (getGlobal().isThereVariable(value))
        return getGlobal().vartable.at(value.getVal());
    ErrorHandler::raiseError({ErrorType::NotDefined, value.getPos()[0],
                              value.getPos()[1], "Identifier is not defined"});
    return Object::NONE;
}
void SymbolTable::setValue(const Token &value, Ref<Object> o) {
    if (isThereVariable(value))
        (vartable[value.getVal()] = o);
    else if (getGlobal().isThereVariable(value))
        getGlobal().vartable[value.getVal()] = o;
    else {
        return ErrorHandler::raiseError({ErrorType::NotDefined,
                                         value.getPos()[0], value.getPos()[1],
                                         "Identifier is not defined"});
    }
}
void SymbolTable::deleteVariable(const Token &value) {
    if (!isThereVariable(value)) {
        return ErrorHandler::raiseError({ErrorType::NotDefined,
                                         value.getPos()[0], value.getPos()[1],
                                         "Identifier is not defined"});
    }
    vartable.erase(value.getVal());
}
bool SymbolTable::isThereVariable(const Token &value) {
    return vartable.find(value.getVal()) != vartable.end();
}

void SymbolTable::addFunc(const Token &value, Ref<Node> o) {
    if (isThereFunc(value))
        ErrorHandler::raiseError({ErrorType::NotDefined, value.getPos()[0],
                                  value.getPos()[1],
                                  "Identifier already defined"});
    funcTable[value.getVal()] = o;
}
Ref<Node> SymbolTable::getFunc(const Token &value) {
    if (isThereFunc(value))
        return funcTable.at(value.getVal());
    if (getGlobal().isThereFunc(value))
        return getGlobal().funcTable.at(value.getVal());
    ErrorHandler::raiseError({ErrorType::NotDefined, value.getPos()[0],
                              value.getPos()[1], "Identifier is not defined"});
    return nullptr;
}
void SymbolTable::setFunc(const Token &value, Ref<Node> o) {
    if (!SymbolTable::isThereFunc(value)) {
        return ErrorHandler::raiseError({ErrorType::NotDefined,
                                         value.getPos()[0], value.getPos()[1],
                                         "Identifier is not defined"});
    }
    funcTable[value.getVal()] = o;
}
void SymbolTable::deleteFunc(const Token &value) {
    if (!SymbolTable::isThereFunc(value)) {
        return ErrorHandler::raiseError({ErrorType::NotDefined,
                                         value.getPos()[0], value.getPos()[1],
                                         "Identifier is not defined"});
    }
    funcTable.erase(value.getVal());
}
bool SymbolTable::isThereFunc(const Token &value) {
    return funcTable.find(value.getVal()) != funcTable.end();
}

void SymbolTable::clear() { vartable.clear(); }
SymbolTable &SymbolTable::getGlobal() {
    static SymbolTable global;
    return global;
}

}; // namespace CulLang