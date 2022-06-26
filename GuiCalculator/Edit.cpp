#include "pch.h"

#include "Edit.h"

#include "Utility.h"

Edit::Edit(const sf::Vector2u& size,
           const sf::Vector2f& position,
           std::string text)
	:size_(size),
	position_(position),
	text_(std::move(text))
{}

std::string Edit::getText() const
{
	return text_;
}

void Edit::setText(const std::string& text)
{
	text_ = text;
}

void Edit::draw(sf::RenderWindow& window) const
{
	sf::RectangleShape body(ConvertFrom<float, unsigned>(size_));
	body.setPosition(position_);
	body.setFillColor(sf::Color::White);
	body.setOutlineThickness(5);
	body.setOutlineColor({200, 200, 200});
	window.draw(body);
	sf::String line(text_.c_str());
	sf::Font font;
	auto success = font.loadFromFile("OpenSans-Regular.ttf");
	if(!success)
	{
		throw std::runtime_error("Error loading font");
	}
	sf::Text printable_text(line, font, calculateOptimalLetterSize());
	printable_text.setFillColor(sf::Color::Black);
	printable_text.setOutlineThickness(0);
	printable_text.setPosition(calculateCenteredTextPosition());
	window.draw(printable_text);
}

sf::Vector2f Edit::calculateCenteredTextPosition()const
{
	auto letter_size = calculateOptimalLetterSize();
	return { position_.x,
		position_.y + size_.y / 2 - letter_size / 2 };
}

unsigned Edit::calculateOptimalLetterSize() const
{
	if(text_.empty())
	{
		return 0;
	}
	return std::min(size_.y, size_.x / text_.size());
}
