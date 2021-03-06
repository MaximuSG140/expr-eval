#include "pch.h"

#include "Edit.h"

#include "Utility/Utility.h"

Edit::Edit(const sf::Vector2u& size,
           const sf::Vector2f& position,
           std::string text)
	:size_(size),
	position_(position),
	text_(std::move(text))
{
	auto success = font_.loadFromFile("Fonts/OpenSans-Regular.ttf");
	if(!success)
	{
		throw std::runtime_error("Error loading font");
	}
}


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
	sf::String line(text_);
	sf::Text printable_text(line, 
		font_, 
		calculateOptimalLetterSize());
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
	unsigned left_border = 0, right_border = size_.y;
	sf::String line(text_);
	sf::Text printing_text(line, font_, right_border);
	while(right_border - left_border > 1)
	{
		unsigned middle_value = (right_border + left_border) / 2;
		printing_text.setCharacterSize(middle_value);
		if(printing_text.getLocalBounds().width < size_.x)
		{
			left_border = middle_value;
		}
		else
		{
			right_border = middle_value;
		}
	}
	return left_border;
}
