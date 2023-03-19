#pragma once
#include "Utilities.h"

namespace CulLang {
class PreProcessor {
  public:
    PreProcessor(const std::string &in) : input(in) {}

    std::string givePredicate();
    std::string format();
    void removeReductantNullLine();
    void removeLine();
    void removeMultiLineComment();
    void removeReductantSpaces();
    void removeReductantTabs();


  private:
    const std::string &input;
    int currentIdx;
    std::string out;
};
std::string PreProcessor::givePredicate() {
    std::string predicate;
    predicate += out.back();
    predicate += input[currentIdx];
    return predicate;
}
std::string PreProcessor::format() {

    for (currentIdx = 0; currentIdx < input.size(); currentIdx++) {

        if (givePredicate() == "/*")
            removeMultiLineComment();
        if (givePredicate() == "//")
            removeLine();
        if (givePredicate() == "\n\n" || givePredicate() == "{\n") {
            removeReductantNullLine();
        }
        if (givePredicate() == "  "||givePredicate() == "\n " || givePredicate() == "{ "){
            removeReductantSpaces();
        }
        if (givePredicate() == "\n\t") {
            removeReductantTabs();
        }
        if (givePredicate() == ":{") {
            out+=" ";
        }
        if (input[currentIdx] == '}' && givePredicate() != "\n}") {
            out+="\n";
        }
        out += input[currentIdx];
    }

    return out;
}

void PreProcessor::removeReductantNullLine() {
    while (input[currentIdx] == '\n')
        currentIdx++;
}
void PreProcessor::removeLine() {
    out.pop_back();
    while (input[currentIdx] != '\n')
        currentIdx++;
    currentIdx++;
}

void PreProcessor::removeMultiLineComment() {
    out.pop_back();
    currentIdx++;
    
    while (givePredicate() != "*/")
        currentIdx++;
    currentIdx++;
}

void PreProcessor::removeReductantSpaces() {
    while (input[currentIdx] == ' ')
        currentIdx++;
}

void PreProcessor::removeReductantTabs() {
    while (input[currentIdx] == '\t')
        currentIdx++;
}

} // namespace CulLang