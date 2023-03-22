#pragma once
#include <string>
#include <array>
namespace CulLang{
enum TokenType
{
	// datatype
	culDataTypesStart = 0,
	culNone = 0,
	culInt,
	culFloat,
	culStr,
	culBool,
	culDataTypesEnd,
	// special symbol
	culOperatorsStart = culDataTypesEnd,
	culIPower = culDataTypesEnd,
	culIPlus,
	culIMinus,
	culIMul,
	culIDiv,
	culIMod,
	culPower,
	culIncrement,
	culDecrement,


	culIsEqual,
	culNotEqual,
	culGreaterEqual,
	culLesserEqual,
	culGreater,
	culLesser,

	culPlus,
	culMinus,
	culMul,
	culDiv,
	culMod,

	culColon,
	culPipe,
	culBackSlash,

	culLParen,
	culRParen,
	culLCurly,
	culRCurly,
	culEqual,
	culOperatorsEnd,
	culIndentifier=culOperatorsEnd,
	culNewLine,
	culKeyword,
	culTotal
};
using Datatypes = TokenType;
const std::array<std::string,culTotal> TokenTypeStr = {
	// datatype
	"NULL",
	"INT",
	"FLOAT",
	"STR",
	"BOOL",
	"**=",
	"+=",
	"-=",
	"*=",
	"/=",
	"%=",
	"**",
	"++",
	"--",


	"==",
	"!=",
	">=",
	"<=",
	">",
	"<",

	"+",
	"-",
	"*",
	"/",
	"%",

	":",
	"|",
	"\\",

	"(",
	")",
	"{",
	"}",
	"=",
	"identifier",
	"\\n"
	"keyword",
	};

	constexpr TokenType  culSlash = culDiv;

const size_t SizeOfDataType[culDataTypesEnd] =
	{
		0,
		sizeof(int),
		sizeof(float),
		0};

const std::array<char,3>stringSymbols{'"','\'','`'};

}