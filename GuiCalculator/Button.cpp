#include "Button.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

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
	body.setOutlineThickness(5);
	body.setOutlineColor({200, 200, 200});
	window.draw(body);
	sf::Font font;
	font.loadFromFile("OpenSans-Regular.ttf");
	sf::String line(text_.c_str());
	sf::Text printable_text(line, font);
	printable_text.setPosition(position_);
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
