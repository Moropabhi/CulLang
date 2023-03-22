#pragma once
#include <vector>

#include "debug/ErrorHandler.h"
#include "KeyWord.h"
#include "Token.h"
#include "Utilities.h"

namespace CulLang {
class Lexer {
  public:
    Lexer() = default;

    std::vector<Token> make_tokens(std::string text);

  private:
    void advance();
    void recede();

    void getSymbol(std::vector<Token> &tokens);
    void getString(std::vector<Token> &tokens);
    void getNumber(std::vector<Token> &tokens);
    void getIdentifier(std::vector<Token> &tokens);
    void getInvalidCharErr() {
        

        Str message = "' ";
        message += m_CurrentChar;
        message += " ' is an invalid character";
        auto a = m_Pos;
        a.idx++;
        a.col++;
        ErrorHandler::raiseError({InvalidCharacterError, m_Pos, a, message});
    }
    inline bool ifDigit(char c) { return '0' <= c && c <= '9'; }
    inline bool ifAlpha(char c) {
        return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || c == '_';
    }
    bool isOperator(std::vector<Token> &tokens);

  private:
    std::string m_Text{};
    Position m_Pos{};
    char m_CurrentChar{};
};

std::vector<Token> Lexer::make_tokens(std::string a) {
    m_Text = a;
    m_Pos = {0, 1, 1};
    m_CurrentChar = m_Text[0];
    m_Pos.text = std::make_shared<std::string>(m_Text);

    std::vector<Token> tokens;

    while (m_CurrentChar) {
        if (ifDigit(m_CurrentChar)) {
            getNumber(tokens);
        } else if (ifAlpha(m_CurrentChar)) {
            getIdentifier(tokens);
        } else {
            getSymbol(tokens);
        }
    }

    return tokens;
}
void Lexer::advance() {
    m_Pos.advance(m_CurrentChar);
    m_CurrentChar = m_Text[m_Pos.idx];
}
void Lexer::recede() {
    m_Pos.recede(m_CurrentChar);
    m_CurrentChar = m_Text[m_Pos.idx];
}

void Lexer::getSymbol(std::vector<Token> &tokens) {
    // if (!m_CurrentChar)
    //	return;

    if (m_CurrentChar == ' ')
        return advance();

    if (m_CurrentChar == '\n') {
        tokens.push_back({m_Pos, m_Pos.getAdvanced(m_CurrentChar), culNewLine});
        return advance();
    }
    if (std::find(stringSymbols.begin(), stringSymbols.end(), m_CurrentChar) !=
        stringSymbols.end()) {
        return getString(tokens);
    }
    if (m_CurrentChar == '.') {
        advance();
        if (!ifDigit(m_CurrentChar))
            return getInvalidCharErr();

        Str num = "0.";
        auto pos0 = m_Pos;
        do {
            num += m_CurrentChar;
            advance();
        } while (ifDigit(m_CurrentChar));

        if (m_CurrentChar == '.')
            getInvalidCharErr();

        tokens.push_back({pos0, m_Pos, culFloat, num});
    }
    if (!isOperator(tokens)) {
        getInvalidCharErr();
        advance();
    }
}
void Lexer::getNumber(std::vector<Token> &tokens) {
    Str num;
    TokenType type = culInt;
    const auto pos0 = m_Pos;
    auto isTherePeriod = false;

    do {
        num += m_CurrentChar;
        advance();

        if (m_CurrentChar == '.') {
            if (isTherePeriod)
                return getInvalidCharErr();
            isTherePeriod = true;
            type = culFloat;
            num += '.';
            advance();
        }
    } while (ifDigit(m_CurrentChar));

    if (num.back() == '.')
        num += '0';

    tokens.push_back({pos0, m_Pos, type, num});
}
void Lexer::getIdentifier(std::vector<Token> &tokens) {
    Str identifier;
    TokenType type = culIndentifier;
    const auto pos0 = m_Pos;
    do {
        identifier += m_CurrentChar;
        advance();
    } while (ifDigit(m_CurrentChar) || ifAlpha(m_CurrentChar));
    if (identifier == CulKeywordStr[culTrue] ||
        identifier == CulKeywordStr[culFalse])
        type = culBool;
    else if (std::find(CulKeywordStr.begin(), CulKeywordStr.end(),
                       identifier) != CulKeywordStr.end())
        type = culKeyword;
    tokens.push_back({pos0, m_Pos, type, identifier});
}
void Lexer::getString(std::vector<Token> &tokens) {
    std::string s;
    char start = m_CurrentChar;
    auto pos0 = m_Pos;
    advance();
    while (m_CurrentChar && m_CurrentChar != start) {
        s.push_back(m_CurrentChar);
        advance();
    }
    if (!m_CurrentChar) {
        std::string message = "Expected and ending (";
        message += start;
        message += ") in the end";
        return ErrorHandler::raiseError({SyntaxError, pos0, m_Pos, message});
    }
    advance();
    return tokens.push_back({pos0, m_Pos, culStr, s});
}
bool Lexer::isOperator(std::vector<Token> &tokens) {
    bool isOp = false;
    Str op;
    op.reserve(3);

    for (int i = 0; i < TokenTypeStr[culOperatorsStart].length(); i++) {
        if (isalnum(m_CurrentChar) || m_CurrentChar == '_' ||
            m_CurrentChar == ' '||
            m_CurrentChar == '\n')
            break;
        op += m_CurrentChar;
        advance();
    }
    LOG(op);
    auto val = std::find(TokenTypeStr.begin() + culOperatorsStart,
                         TokenTypeStr.begin() + culOperatorsEnd, op) -
               TokenTypeStr.begin();

    if (val != culOperatorsEnd) {
        tokens.push_back(
            {m_Pos.getReceded(m_CurrentChar), m_Pos, (TokenType)val});
        return true;
    }
    return false;
}
} // namespace CulLang