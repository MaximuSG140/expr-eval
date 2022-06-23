#include "Converter.h"

#include <algorithm>
#include <stack>
#include <stdexcept>

#include "ExpressionTokenizer.h"

Operation ConvertOperationCharacterToEnum(const char operation_character)
{
	switch(operation_character)
	{
	case '+':
		return Operation::ADD;
	case '-':
		return Operation::SUB;
	case '*':
		return Operation::MUL;
	case '/':
		return Operation::DIV;
	default: 
		throw std::runtime_error("Wrong op-character");
	}
}

Converter::Converter(std::unordered_map<Operation, size_t> priorities)
	:priorities_(std::move(priorities))
{}

std::string Converter::convertToString(const std::string& expr)
{
	std::string result;
	result.reserve(expr.length() - std::count_if(expr.begin(),
													expr.end(),
													[](const char c)
													{
														return c == '(' || c == ')';
													}));
	std::stack<Token> proxy_stack;
	ExpressionTokenizer tokens(expr);
	while (tokens.hasTokens())
	{
		auto current_token = tokens.getToken();
		if (current_token.type == TokenType::VALUE)
		{
			result += "\"" + current_token.character_value + "\"";
			continue;
		}
		if (current_token.character_value == "(")
		{
			proxy_stack.push(current_token);
			continue;
		}
		if (current_token.character_value == ")")
		{
			while (proxy_stack.top().character_value != "(")
			{
				result += proxy_stack.top().character_value;
				proxy_stack.pop();
			}
			proxy_stack.pop();
			continue;
		}

		auto get_priority = [&](const Token& t)
		{
			return priorities_.at(ConvertOperationCharacterToEnum(t.character_value[0]));
		};

		while (get_priority(proxy_stack.top()) >= get_priority(current_token))
		{
			result += proxy_stack.top().character_value;
			proxy_stack.pop();
		}
		proxy_stack.push(current_token);
	}
	while (!proxy_stack.empty())
	{
		result += proxy_stack.top().character_value;
		proxy_stack.pop();
	}
	return result;
}

std::vector<Token> Converter::convertToTokenSequence(const std::string& expr)
{
	std::vector<Token> res;
	std::stack<Token>  proxy_stack;
	ExpressionTokenizer tokens(expr);
	while(tokens.hasTokens())
	{
		auto current_token = tokens.getToken();
		if(current_token.type == TokenType::VALUE)
		{
			res.push_back(current_token);
			continue;
		}
		if(current_token.character_value == "(")
		{
			proxy_stack.push(current_token);
			continue;
		}
		if(current_token.character_value == ")")
		{
			while(proxy_stack.top().character_value != "(")
			{
				res.push_back(proxy_stack.top());
				proxy_stack.pop();
			}
			proxy_stack.pop();
			continue;
		}

		auto get_priority = [&](const Token& t)
		{
			return  priorities_.at(ConvertOperationCharacterToEnum(t.character_value[0]));
		};

		while(!proxy_stack.empty() && proxy_stack.top().character_value != "(" &&
			get_priority(proxy_stack.top()) >= get_priority(current_token))
		{
			res.push_back(proxy_stack.top());
			proxy_stack.pop();
		}
		proxy_stack.push(current_token);
	}
	while(!proxy_stack.empty())
	{
		res.push_back(proxy_stack.top());
		proxy_stack.pop();
	}
	return res;
}
