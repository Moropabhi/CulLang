#pragma once
#include "Utilities.h"
namespace CulLang
{
	struct Text
	{
		std::string data;
		//std::vector<int> newline;
		void generate()
		{

			//while (newline.back()!=data.npos)data.find_first_of('c');
		}
	};
	struct Position
	{
		int idx = 0;
		int ln = 1;
		int col = 0;
		std::string filename="CulLang Shell";
		std::string fileContext;
		Ref<std::string> text;
		Position()=default;
		Position(int idx,int ln,int col)
		: idx(idx),ln(ln),col(col)
		{

		}

		void advance(char current_char);
		void recede(char current_char);
		Position getAdvanced(char current_char);
		Position getReceded(char current_char);
		int lastLineCol = 0;
	};
}

namespace CulLang
{

	void Position::advance(char current_char)
	{
		if(!current_char)
			return;
		idx++;
		col++;

		if (current_char == '\n')
		{
			ln++;
			lastLineCol=col;
			col = 0;
		}

	}
	void Position::recede(char current_char) 
	{
		if(!current_char ||idx==0)
			return;
		idx--;
		col--;

		if (current_char == '\n')
		{
			ln--;
			col = lastLineCol;
		}
	}

	Position Position::getAdvanced(char current_char)
	{
		Position pos=*this;
		if(!current_char)
			return pos;
		pos.idx++;
		pos.col++;

		if (current_char == '\n')
		{
			pos.ln++;
			pos.col = 0;
		}
		return pos;

	}
	Position Position::getReceded(char current_char) 
	{
		Position pos;
		pos = (*this);
		if(!current_char ||idx==0)
			return pos;
		pos.idx--;
		pos.col--;
		if (current_char == '\n')
		{
			pos.ln--;
			pos.col = lastLineCol;
		}
		return pos;
	}
}