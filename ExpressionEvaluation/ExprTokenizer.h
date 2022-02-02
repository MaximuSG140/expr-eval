#pragma once
#include <set>
#include <string>

#include "Token.h"

class ExprTokenizer
{
public:
	explicit ExprTokenizer(std::string expression, std::set<char>spec_chars = {'+', '-', '*', '/'});
	bool HasTokens() const;
	Token GetToken();
private:
	std::string char_expr_;
	size_t cursor_ = 0;
	std::set<char> spec_symbols_;
};

