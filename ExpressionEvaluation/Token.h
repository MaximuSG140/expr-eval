#pragma once
#include <string>

enum class TokenType
{
	OPERATOR,
	VALUE
};

struct Token
{
	TokenType type;
	std::string character_value;
};