#include "ExprTokenizer.h"
#include <algorithm>

ExprTokenizer::ExprTokenizer(std::string expression, std::set<char> spec_chars)
	:char_expression_(std::move(expression)),
	spec_symbols_(std::move(spec_chars))
{}

bool ExprTokenizer::HasTokens() const
{
	return cursor_ == char_expression_.length();
}

Token ExprTokenizer::GetToken()
{
	auto lt_it = char_expression_.begin() + cursor_;
	auto rt_it = std::find_if(lt_it,
		char_expression_.end(),
		[&](const char c) {return spec_symbols_.count(c); });
	if(lt_it == rt_it)
	{
		cursor_++;
		return { TokenType::OPERATOR, std::string{*lt_it} };
	}
	cursor_ = rt_it - lt_it;
	return { TokenType::VALUE, std::string(lt_it, rt_it) };
}
