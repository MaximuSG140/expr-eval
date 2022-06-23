#include "ExpressionTokenizer.h"
#include <algorithm>

ExpressionTokenizer::ExpressionTokenizer(std::string expression, std::set<char> special_symbols)
	:expression_(std::move(expression)),
	special_symbols_(std::move(special_symbols))
{
	expression_.erase(std::remove(expression_.begin(),
									  expression_.end(),
									  ' '),
					expression_.end());
}

bool ExpressionTokenizer::hasTokens() const
{
	return position_ != expression_.length();
}

Token ExpressionTokenizer::getToken()
{
	auto left_iterator = expression_.begin() + position_;
	auto right_iterator = std::find_if(left_iterator,
		expression_.end(),
		[&](const char c)
		{
			return special_symbols_.count(c);
		});
	if(left_iterator == right_iterator)
	{
		position_++;
		return { TokenType::OPERATOR, std::string{*left_iterator} };
	}
	position_ = right_iterator - expression_.begin();
	return { TokenType::VALUE, std::string(left_iterator, right_iterator) };
}
