#include "pch.h"

#include "Button.h"


Button::Button(const sf::Vector2u& size,
               const sf::Vector2f& position,
               std::string text,
               std::function<void()> on_click_handler)
	:size_(size),
	position_(position),
	click_handler_(std::move(on_click_handler)),
	text_(std::move(text))
{}

void Button::draw(sf::RenderWindow& window) const
{
	sf::RectangleShape body(size_);
	body.setPosition(position_);
	body.setFillColor(sf::Color::Cyan);
	body.setOutlineThickness(1);
	body.setOutlineColor({200, 200, 200});
	window.draw(body);
	sf::Font font;
	auto success = font.loadFromFile("Fonts/OpenSans-Regular.ttf");
	if(!success)
	{
		throw std::runtime_error("Error loading font");
	}
	sf::String line(text_);
	sf::Text printable_text(line, font, TEXT_CHARACTER_SIZE);
	printable_text.setPosition(getPositionForPrintingCenteredText());
	printable_text.setFillColor(sf::Color::Black);
	window.draw(printable_text);
}

void Button::tryActivate(const sf::Vector2f& mouse_position) const
{
	if(checkoutPosition(mouse_position))
	{
		onClick();
	}
}

bool Button::checkoutPosition(const sf::Vector2f& mouse_position) const
{
	auto left_border = position_.x;
	auto right_border = position_.x + size_.x;
	auto upper_border = position_.y;
	auto bottom_border = position_.y + size_.y;
	return mouse_position.x >= left_border && mouse_position.x < right_border&&
		mouse_position.y >= upper_border && mouse_position.y < bottom_border;
}

void Button::onClick() const
{
	click_handler_();
}

sf::Vector2f Button::getPositionForPrintingCenteredText() const
{
	float x = size_.x / 2 - text_.size() * TEXT_CHARACTER_SIZE / 2;
	float y = size_.y / 2 - TEXT_CHARACTER_SIZE / 2;
	return { position_.x + x,
		position_.y + y };
}
