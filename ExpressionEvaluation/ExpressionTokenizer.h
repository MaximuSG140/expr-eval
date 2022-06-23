#pragma once
#include <set>
#include <string>

#include "Token.h"

class ExpressionTokenizer
{
public:
	explicit ExpressionTokenizer(std::string expression,
		std::set<char> special_symbols = {'+', '-', '*', '/', '(', ')'});
	bool hasTokens() const;
	Token getToken();
private:
	std::string expression_;
	std::string::size_type position_ = 0;
	std::set<char> special_symbols_;
};

