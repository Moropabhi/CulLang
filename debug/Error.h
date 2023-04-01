#pragma once

#include "../Position.h"
#include <array>

namespace CulLang {

enum ErrorType {
    NoError,
    UnknownError,
    InvalidCharacterError,
    SyntaxError,
    ValueError,
    ZeroDivision,
    InvalidOperation,
    NotDefined,
    AlreadyDefined,
    FeatureNotImplementedYet,
    SemanticsError,
    NoOfError

};

class Error {
  public:
    Error(ErrorType type, std::array<Position, 2> pos,
          std::string message = "") {}

    Error(ErrorType type, const Position &start_pos, const Position &end_pos,
          const std::string &message = "")
        : type(type), pos({start_pos, end_pos}), message(message) {}

    Error(ErrorType type, std::string message = "")
        : type(type), message(message) {}

    //\returns type of an error
    ErrorType getType() const { return type; }

    // sets the postion of the error
    void setPos(const std::array<Position, 2> &pos) { this->pos = pos; }
    // sets the postion of the error
    void setPos(const Position &start, const Position &end) {
        pos[0] = start;
        pos[1] = end;
    }

    // raise the error to the console
    void raise() const {
#if !THROW_ERROR
        if (!type)
            return;
        std::string text;
        std::cout << "here\n";
        std::cout << pos[1].text << '\n';
        Str liner;

        liner.resize(pos[0].idx, '~');
        liner.resize(pos[1].idx, '^');
        liner.resize(pos[0].text->size(), '~');
        std::cout << liner << '\n';
        std::cout << '\n';
        std::cout << ERRORS[type] << ": " << message << '\n';
        std::cout << "File : " << pos[0].filename << '\n'
                  << "Line : " << pos[0].ln << '\n'
                  << "Pos : " << pos[0].col << '\n';
#endif
    }

  protected:
    ErrorType type;
    std::array<Position, 2> pos = {};
    Str message = "";
#if !THROW_ERROR
    std::string ERRORS[NoOfError] = {"NoError",
                                     "UnknownError",
                                     "InvalidCharacterError",
                                     "SyntaxError",
                                     "ValueError",
                                     "ZeroDivision",
                                     "InvalidOperation",
                                     "NotDefined",
                                     "AlreadyDefined",
                                     "FeatureNotImplementedYet",
                                     "SemanticsError"};
#endif
};
} // namespace CulLang