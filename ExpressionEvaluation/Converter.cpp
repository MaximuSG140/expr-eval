#include "Converter.h"

#include <algorithm>
#include <stack>
#include <stdexcept>

#include "ExprTokenizer.h"

Operation CvtToEnum(const char operator_char)
{
	switch(operator_char)
	{
	case '+': return Operation::ADD;
	case '-': return Operation::SUB;
	case '*': return Operation::MUL;
	case '/': return Operation::DIV;
	default: throw std::runtime_error("Wrong op-character");
	}
}

Converter::Converter(std::unordered_map<Operation, size_t> priorities)
	:priorities_(std::move(priorities))
{}

std::string Converter::CvtToString(const std::string& expr)
{
	std::string res;
	res.reserve(expr.length() - std::count_if(expr.begin(),
													expr.end(),
													[](const char c)
													{
														return c == '(' || c == ')';
													}));
	std::stack<Token>  proxy_stack;
	ExprTokenizer tokens(expr);
	while (tokens.HasTokens())
	{
		Token current_token = tokens.GetToken();
		if (current_token.type == TokenType::VALUE)
		{
			res += "\"" + current_token.char_token + "\"";
			continue;
		}
		if (current_token.char_token == "(")
		{
			proxy_stack.push(current_token);
			continue;
		}
		if (current_token.char_token == ")")
		{
			while (proxy_stack.top().char_token != "(")
			{
				res += proxy_stack.top().char_token;
				proxy_stack.pop();
			}
			proxy_stack.pop();
			continue;
		}

		auto get_prior = [&](const Token& t)
		{
			return  priorities_.at(CvtToEnum(t.char_token[0]));
		};

		while (get_prior(proxy_stack.top()) >= get_prior(current_token))
		{
			res += proxy_stack.top().char_token;
			proxy_stack.pop();
		}
		proxy_stack.push(current_token);
	}
	while (!proxy_stack.empty())
	{
		res += proxy_stack.top().char_token;
		proxy_stack.pop();
	}
	return res;
}

std::vector<Token> Converter::CvtToTokenSeq(const std::string& expr)
{
	std::vector<Token> res;
	std::stack<Token>  proxy_stack;
	ExprTokenizer tokens(expr);
	while(tokens.HasTokens())
	{
		Token current_token = tokens.GetToken();
		if(current_token.type == TokenType::VALUE)
		{
			res.push_back(current_token);
			continue;
		}
		if(current_token.char_token == "(")
		{
			proxy_stack.push(current_token);
			continue;
		}
		if(current_token.char_token == ")")
		{
			while(proxy_stack.top().char_token != "(")
			{
				res.push_back(proxy_stack.top());
				proxy_stack.pop();
			}
			proxy_stack.pop();
			continue;
		}

		auto get_prior = [&](const Token& t)
		{
			return  priorities_.at(CvtToEnum(t.char_token[0]));
		};

		while(get_prior(proxy_stack.top()) >= get_prior(current_token))
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
