#pragma once
#include "Position.h"
#include "TokenType.h"
#include "datatypes/Bool.h"
#include "datatypes/CulString.h"
#include "datatypes/Float.h"
#include "datatypes/Int.h"
#include "datatypes/Object.h"

namespace CulLang {
class Token {
  public:
    Token(const Position &posStart, const Position &posEnd, TokenType type_,
          const std::string &a = "")
        : type(type_), value(a), posStart(posStart), posEnd(posEnd) {}
    ~Token() = default;

    Token(Token &&tok)
        : type(tok.type), value(std::move(tok.value)),
          posStart(std::move(tok.posStart)), posEnd(std::move(tok.posEnd)) {}
    auto operator=(const Token &tok) 
	{
		type=tok.type;
		value=tok.value;
		posStart=tok.posStart;
		posEnd=tok.posEnd;
	}
    Token(const Token &tok)
        : type(tok.type), value(std::move(tok.value)),
          posStart(std::move(tok.posStart)), posEnd(std::move(tok.posEnd)) {}

    TokenType getType() const { return type; }
    static std::string getTypeStr(const TokenType &type) {
        return TokenTypeStr[type];
    }
    std::string getTypeStr() const { return TokenTypeStr[type]; }
    std::array<Position, 2> getPos() const { return {posStart, posEnd}; }
    std::string getVal() const

    {
        return value;
    }
    Ref<Object> getValueConverted() const;
    std::string getConvertedtoC() const;

    static bool checkIfEqual(const Token *v, TokenType t,
                             bool countNull = false);
    static bool checkIfNotEqual(const Token *v, TokenType t,
                                bool countNull = true);

  private:
    TokenType type;
    std::string value;
    Position posStart;
    Position posEnd;
};
} // namespace CulLang

namespace CulLang {
Ref<Object> Token::getValueConverted() const {
    switch (type) {
    case culInt:
        return std::make_shared<Int>(value);
    case culFloat:
        return std::make_shared<Float>(value);
    case culStr:
        return std::make_shared<String>(value);
    case culBool:
        return std::make_shared<Bool>(value);
    default:
        std::string str = "This type '";
        str += TokenTypeStr[type];
        str += "' is not implemented yet for The class 'Tokens'";
        ErrorHandler::raiseError(
            {FeatureNotImplementedYet,
             "This type is not implemented yet for The class 'Tokens'"});
        return Object::NONE;
    }
}

std::string Token::getConvertedtoC() const {
    switch (type) {
    case culInt:
        return Int(value).getInC();
    case culFloat:
        return Float(value).getInC();
    case culStr:
        return String(value).getInC();
    case culBool:
        return Bool(value).getInC();
    default:
        std::string str = "This type '";
        str += TokenTypeStr[type];
        str += "' is not implemented yet for The class 'Tokens'";
        ErrorHandler::raiseError(
            {FeatureNotImplementedYet,
             "This type is not implemented yet for The class 'Tokens'"});
        return "";
    }
}

bool Token::checkIfEqual(const Token *v, TokenType t, bool countNull) {
    return (v && v->type == t) || (countNull && !v);
}

bool Token::checkIfNotEqual(const Token *v, TokenType t, bool countNull) {
    return (v && v->type != t) || (countNull && !v);
}

} // namespace CulLang
