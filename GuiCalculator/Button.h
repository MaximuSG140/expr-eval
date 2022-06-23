#pragma once
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>

class Button
{
public:
	explicit Button(const sf::Vector2u& size,
		const sf::Vector2f& position,
		std::string text,
		std::function<void()> on_click_handler);

	void draw(sf::RenderWindow& window)const;

	void tryActivate(const sf::Vector2f& mouse_position)const;
	bool checkoutPosition(const sf::Vector2f& mouse_position)const;
	void onClick()const;
private:
	sf::Vector2f size_;
	sf::Vector2f position_;
	std::function<void()> click_handler_;
	std::string text_;
};

