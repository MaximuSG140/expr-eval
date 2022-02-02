#include"Evaluate.h"

#include <stack>
#include <stdexcept>

#include "Converter.h"

int Evaluate(const std::string& expr)
{
	Converter c;
	auto tokens = c.CvtToTokenSeq(expr);
	std::stack<int> values;
	for(auto cur_token : tokens)
	{
		if(cur_token.type == TokenType::VALUE)
		{
			values.push(std::stoi(cur_token.char_token));
		}
		else
		{
			int fst = values.top();
			values.pop();
			int scd = values.top();
			values.pop();
			std::swap(fst, scd);
			switch(CvtToEnum(cur_token.char_token[0]))
			{
			case Operation::ADD:
				values.push(fst + scd);
				break;
			case Operation::SUB:
				values.push(fst - scd);
				break;
			case Operation::MUL:
				values.push(fst * scd);
				break;
			case Operation::DIV:
				values.push(fst / scd);
				break;
			default: 
				throw std::runtime_error("Bad enum");
			}
		}
	}
	if(values.size() > 1 || values.empty())
	{
		throw std::runtime_error("Bad expression");
	}
	return values.top();
}
