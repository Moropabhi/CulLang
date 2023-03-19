#pragma once
#include "KeyWord.h"
#include "SymbolTable.h"
#include "Utilities.h"
#include "nodes/AssignmentOperatorNode.h"
#include "nodes/AugumentedOpNode.h"
#include "nodes/BinaryOperatorNode.h"
#include "nodes/BlockNode.h"
#include "nodes/ForNode.h"
#include "nodes/FuncNode.h"
#include "nodes/IfNode.h"
#include "nodes/PrintNode.h"
#include "nodes/UnaryOperatorNode.h"
#include "nodes/VarAccessNode.h"
#include "nodes/VarAllocateNode.h"
#include "nodes/WhileNode.h"
#include "nodes/ifElifNode.h"

#define IS_KEYWORD(token, Keyword) (token->getVal() == CulKeywordStr[Keyword])

namespace CulLang {

enum ParserConstant {
    atom,
    power,
    factor,
    term,
    expr,
    condition,
    stmt,
    program
};

class Parser {
    std::vector<Token> &tokens;
    int tokenIdx = 0;
    const Token *currentToken;

  public:
    Parser(std::vector<Token> &tokens);
    std::vector<Ref<Node>> &parse();

  private:
    void advance();
    void retreat();

    Ref<Node> atom();
    Ref<Node> power();
    Ref<Node> factor();
    Ref<Node> term();
    Ref<Node> condition();
    Ref<Node> expr();
    Ref<Node> stmt();
    Ref<Node> block();
    void program();

    Ref<Node> evaluate(ParserConstant p);
    Ref<Node> checkKeyword();

    template <ParserConstant type1, ParserConstant type2, size_t Size>
    Ref<Node> BinaryOperation(const std::array<TokenType, Size> operators) {
        // evaluating left node
        Ref<Node> left = evaluate(type1);
        if (!left)
            return left;

        if (currentToken->getType() == culNewLine ||
            currentToken->getType() == culKeyword)
            return left;

        if (currentToken && !(currentToken->getType() < culOperatorsEnd &&
                              currentToken->getType() >= culOperatorsStart)) {
            ErrorHandler::raiseError({ErrorType::SyntaxError,
                                      currentToken->getPos(),
                                      "expected an operator"});
            return nullptr;
        }
        // after getting the left node
        while (currentToken && checkInArray<TokenType, Size>(
                                   currentToken->getType(), operators)) {
            const auto opToken = currentToken;
            auto opPos = currentToken->getPos();
            // getting the right node and evaluating
            advance();
            auto right = evaluate(type2);
            if (!right) {
                ErrorHandler::raiseError(
                    {ErrorType::SyntaxError, opPos,
                     "required an operand for this operator"});
                return nullptr;
            }

            // getting the left and right into one node
            left = std::make_shared<BinaryOperatorNode>(left, opToken, right);
        }
        return left;
    }

    template <ParserConstant type, size_t Size>
    Ref<Node> UnaryOperation(const std::array<TokenType, Size> operators) {
        if (!currentToken)
            return nullptr;
        const auto opToken = currentToken;
        const auto opPos = currentToken->getPos();
        advance();
        Ref<Node> right = evaluate(type);
        if (!right) {
            ErrorHandler::raiseError(
                {SyntaxError, opPos, "required an operand for this operator"});
            return nullptr;
        }
        return std::make_shared<UnaryOperatorNode>(opToken, right);
    }

  private:
    std::vector<Ref<Node>> nodes;
};

Parser::Parser(std::vector<Token> &tokens)
    : tokens(tokens), currentToken(&tokens[0]) {}

std::vector<Ref<Node>> &Parser::parse() {
    program();
    // if (currentToken)
    // {
    // 	ErrorHandler::raiseError({ SyntaxError, currentToken->getPos(), "This is
    // not grammaticlly correct"});
    // }
    return nodes;
}
void Parser::advance() {
    tokenIdx++;
    if (tokenIdx < tokens.size()) {
        currentToken = &tokens[tokenIdx];
    } else {
        currentToken = nullptr;
    }
}
void Parser::retreat() {
    tokenIdx--;
    if (tokenIdx > -1) {
        currentToken = &tokens[tokenIdx];
    } else {
        currentToken = nullptr;
    }
}

Ref<Node> Parser::atom() {
    if (!currentToken)
        return nullptr;
    if (Token::checkIfEqual(currentToken, culLParen)) {
        std::array<Position, 2> pos = currentToken->getPos();
        advance();
        auto res = condition();
        if (!res)
            return res;
        if (Token::checkIfEqual(currentToken, culRParen))
            advance();
        else {
            ErrorHandler::raiseError({SyntaxError, pos[0], pos[1],
                                      "There is no closing bracket of this"});
            return nullptr;
        }
        return res;
    }

    if (Token::checkIfEqual(currentToken, culInt) ||
        Token::checkIfEqual(currentToken, culFloat) ||
        Token::checkIfEqual(currentToken, culStr) ||
        Token::checkIfEqual(currentToken, culBool)) {
        Ref<Node> res = std::make_shared<Node>(currentToken);
        advance();
        return res;
    }
    if (Token::checkIfEqual(currentToken, culIndentifier)) {
        Ref<Node> res = std::make_shared<VarAccessNode>(currentToken);
        advance();
        return res;
    }
    ErrorHandler::raiseError({SyntaxError, currentToken->getPos()[0],
                              currentToken->getPos()[1],
                              "Expected an expression"});
    advance();
    return nullptr;
}
Ref<Node> Parser::power() {
    if (!currentToken)
        return nullptr;
    return BinaryOperation<ParserConstant::atom, ParserConstant::factor, 1>(
        std::array<TokenType, 1>{culPower});
}
Ref<Node> Parser::factor() {
    if (!currentToken)
        return nullptr;
    Ref<Node> res;
    if (Token::checkIfEqual(currentToken, culPlus) ||
        Token::checkIfEqual(currentToken, culMinus)) {
        res = UnaryOperation<ParserConstant::power, 2>(
            std::array<TokenType, 2>{culPlus, culMinus});
    } else {
        res = power();
    }

    if (Token::checkIfEqual(currentToken, culIncrement) ||
        Token::checkIfEqual(currentToken, culDecrement)) {
        res = std::make_shared<UnaryOperatorNode>(currentToken, res);
        advance();
    }
    return res;
}
Ref<Node> Parser::term() {
    if (!currentToken)
        return nullptr;
    return BinaryOperation<ParserConstant::factor, ParserConstant::factor, 3>(
        std::array<TokenType, 3>{culMul, culDiv, culMod});
}
Ref<Node> Parser::expr() {
    if (!currentToken)
        return nullptr;

    return BinaryOperation<ParserConstant::term, ParserConstant::term, 2>(
        std::array<TokenType, 2>{culPlus, culMinus});
}
Ref<Node> Parser::condition() {
    if (!currentToken) {
        return nullptr;
    }

    if (Token::checkIfEqual(currentToken, culKeyword)) {
        return checkKeyword();
    }

    auto var = BinaryOperation<ParserConstant::expr, ParserConstant::expr,
                               (int)culLesser - culIsEqual + 1>({
        culIsEqual,
        culNotEqual,
        culGreaterEqual,
        culLesserEqual,
        culGreater,
        culLesser,
    });
    if (Token::checkIfEqual(currentToken, culKeyword)) {
        if (IS_KEYWORD(currentToken, culAnd) ||
            IS_KEYWORD(currentToken, culOr)) {
            const auto op = currentToken;
            advance();
            var = std::make_shared<BinaryOperatorNode>(var, op, condition());
        } else {
            ErrorHandler::raiseError(
                {SyntaxError, currentToken->getPos(),
                 " this keyword is not meant for this usage. "
                 "See if something can be used"});
            return nullptr;
        }
    }
    return var;
}
Ref<Node> Parser::stmt() {
    if (!currentToken)
        return nullptr;

    if (Token::checkIfEqual(currentToken, culKeyword)) {
        return checkKeyword();
    }

    if (Token::checkIfEqual(currentToken, culIndentifier)) {
        const auto id = currentToken;
        advance();
        if (Token::checkIfEqual(currentToken, culEqual)) {
            advance();
            return std::make_shared<AssignmentOperatorNode>(id, condition());
        }
        if (culIPower <= currentToken->getType() &&
            currentToken->getType() <= culIMod) {
            auto op = currentToken;
            advance();
            return std::make_shared<AugumentedOperatorNode>(id, op,
                                                            condition());
        }

        retreat();
    }
    return condition();
}
Ref<Node> Parser::block() {
    LOG(currentToken->getVal());
    DEBUG_LOG(currentToken->getTypeStr());
    if (currentToken->getType() != culLCurly) {
        return std::make_shared<BlockNode>(std::vector<Ref<Node>>{stmt()});
    }
    advance();

    std::vector<Ref<Node>> stmts;
    Ref<Node> st;
    do {
        //LOG(currentToken->getVal()<<" : "<<currentToken->getTypeStr());
        st = stmt();
        //LOG(currentToken->getVal()<<" : "<<currentToken->getTypeStr());
        if (st) {
            stmts.push_back(st);
            advance();
            //LOG(currentToken->getVal()<<" : "<<currentToken->getTypeStr());
        }
        
    } while (st && currentToken && currentToken->getType() != culRCurly);

    if (currentToken->getType() != culRCurly) {
        ErrorHandler ::raiseError({SyntaxError, currentToken->getPos(),
                                   "expected a curly brace at the end"});
        return nullptr;
    }
    advance();
    return std::make_shared<BlockNode>(std::move(stmts));
}
void Parser::program() {
    while (currentToken) {
        nodes.push_back(stmt());
        advance();
    }
}

Ref<Node> Parser::evaluate(ParserConstant p) {
    switch (p) {
    case ParserConstant::atom:
        return atom();
    case ParserConstant::power:
        return power();
    case ParserConstant::factor:
        return factor();
    case ParserConstant::term:
        return term();
    case ParserConstant::expr:
        return expr();
    case ParserConstant::condition:
        return condition();
    case ParserConstant::stmt:
        return stmt();
    default:
        return {};
    }
}

Ref<Node> Parser::checkKeyword() {
    if (IS_KEYWORD(currentToken, culLet)) {
        advance();
        if (Token::checkIfNotEqual(currentToken, culIndentifier)) {
            ErrorHandler::raiseError({SyntaxError, currentToken->getPos(),
                                      "Expected an identifier"});
            return nullptr;
        }
        const auto id = currentToken;
        advance();
        if (Token::checkIfNotEqual(currentToken, culEqual)) {
            ErrorHandler::raiseError({SyntaxError, currentToken->getPos(),
                                      "Expected an equal sign '='"});
            return nullptr;
        }
        advance();
        return std::make_shared<VarAllocateNode>(id, condition());
    } else if (IS_KEYWORD(currentToken, culPrint)) {
        advance();
        return std::make_shared<PrintNode>(condition());
    } else if (IS_KEYWORD(currentToken, culNot)) {
        const auto op = currentToken;
        advance();
        return std::make_shared<UnaryOperatorNode>(op, condition());
    } else if (IS_KEYWORD(currentToken, culIf)) {
        auto iftok = currentToken;
        advance();
        auto cond = condition();
        if (currentToken->getType() != culColon) {
            ErrorHandler ::raiseError(
                {SyntaxError, currentToken->getPos(), "expected a colon"});
            return nullptr;
        }
        advance();
        Ref<Node> statement = nullptr;
        statement = block();
        //LOG(currentToken->getVal());
        if (!currentToken)
            return std::make_shared<IfNode>(cond, statement);
        // if (currentToken && currentToken->getType() != culNewLine) {
        //     ErrorHandler ::raiseError(
        //         {SyntaxError, currentToken->getPos(), "expected newline"});
        //     return nullptr;
        // }
        //advance();
        std::vector<IfElifNode::ElifCode> elifs;
        if (IS_KEYWORD(currentToken, culElif)) {
            while (IS_KEYWORD(currentToken, culElif)) {
                advance();
                auto cond = condition();
                if (currentToken->getType() != culColon) {
                    ErrorHandler ::raiseError({SyntaxError,
                                               currentToken->getPos(),
                                               "expected a colon"});
                    return nullptr;
                }
                advance();
                auto statement = block();
                elifs.push_back({cond, statement});
                advance();
            }
        }
        if (!IS_KEYWORD(currentToken, culElse))
            if (elifs.size())
                return std::make_shared<IfElifNode>(cond, statement, elifs,
                                                    nullptr);
            else
                return std::make_shared<IfNode>(cond, statement);

        advance();
        if (currentToken->getType() != culColon) {
            ErrorHandler ::raiseError(
                {SyntaxError, currentToken->getPos(), "expected a colon"});
            return nullptr;
        }
        advance();
        auto Elsestatement = block();
        if (elifs.size())
            return std::make_shared<IfElifNode>(cond, statement, elifs,
                                                Elsestatement);
        else
            return std::make_shared<IfNode>(cond, statement, Elsestatement);

    } else if (IS_KEYWORD(currentToken, culWhile)) {
        advance();
        auto cond = condition();
        if (currentToken->getType() != culColon) {
            ErrorHandler ::raiseError(
                {SyntaxError, currentToken->getPos(), "expected a colon"});
            return nullptr;
        }
        advance();
        auto statement = stmt();
        return std::make_shared<WhileNode>(cond, statement);
    } else if (IS_KEYWORD(currentToken, culFor)) {
        advance();
        // std::cout << "for looping\n";
        auto init = stmt();
        // std::cout << "stopped at " << currentToken->getTypeStr()<<' '
        //           << (currentToken->getType() == culBackSlash) << '\n';
        if (currentToken->getType() != culBackSlash) {
            ErrorHandler ::raiseError(
                {SyntaxError, currentToken->getPos(), "expected a '\''"});
            return nullptr;
        }
        advance();
        auto cond = condition();
        // std::cout << "stopped2 at " << currentToken->getTypeStr()<<' '
        //           << (currentToken->getType() == culBackSlash) << '\n';
        if (currentToken->getType() != culBackSlash) {
            ErrorHandler ::raiseError(
                {SyntaxError, currentToken->getPos(), "expected a '\''"});
            return nullptr;
        }
        advance();
        // std::cout << "started3 at " << currentToken->getTypeStr()<<' '
        //           << (tokenIdx)<< currentToken->getVal()<< '\n';
        auto increment = stmt();
        // std::cout << "stopped3 at " << currentToken->getTypeStr()<<' '
        //           << (tokenIdx)<< currentToken->getVal()<< '\n';
        if (currentToken->getType() != culColon) {
            ErrorHandler ::raiseError(
                {SyntaxError, currentToken->getPos(), "expected a colon"});
            return nullptr;
        }
        advance();
        auto statement = stmt();
        return std::make_shared<ForNode>(init, cond, increment, statement);
    } else {
        ErrorHandler::raiseError(
            {ErrorType::FeatureNotImplementedYet, currentToken->getPos(),
             "this keyword is not meant to be in this place "
             "or this feature is not ready to use."});
    }
}

} // namespace CulLang