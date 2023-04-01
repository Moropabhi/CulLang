#pragma once
#include <string>
#include <array>

enum Keywords
{
	culKeyWordStart,
	culNone = culKeyWordStart,
	culLet,
	culPrint,
	culAnd,
	culOr,
	culNot,
	culTrue,
	culFalse,
	culIf,
	culElif,
	culElse,
	culWhile,
	culFor,
	culLoop,
	culBreak,
	culContinue,
	culKeyWordEnd
};

const std::array < std::string,culKeyWordEnd > CulKeywordStr = {
	"none",
	"let",
	"print",
	"and",
	"or",
	"not",
	"true",
	"false",
	"if",
	"elif",
	"else",
	"while",
	"for",
	"loop",
	"break",
	"continue",
	
};