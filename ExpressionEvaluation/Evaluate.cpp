#include"Evaluate.h"

#include <stack>
#include <stdexcept>

#include "Converter.h"

int Evaluate(const std::string& expr)
{
	Converter c;
	auto tokens = c.convertToTokenSequence(expr);
	std::stack<int> values;
	for(auto cur_token : tokens)
	{
		if(cur_token.type == TokenType::VALUE)
		{
			values.push(std::stoi(cur_token.character_value));
		}
		else
		{
			auto first_value = values.top();
			values.pop();
			auto second_value = values.top();
			values.pop();
			std::swap(first_value, second_value);
			switch(ConvertOperationCharacterToEnum(cur_token.character_value[0]))
			{
			case Operation::ADD:
				values.push(first_value + second_value);
				break;
			case Operation::SUB:
				values.push(first_value - second_value);
				break;
			case Operation::MUL:
				values.push(first_value * second_value);
				break;
			case Operation::DIV:
				values.push(first_value / second_value);
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
