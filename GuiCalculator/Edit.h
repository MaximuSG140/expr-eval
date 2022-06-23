#pragma once
#include "pch.h"

class Edit
{
public:
	explicit Edit(const sf::Vector2u& size,
		const sf::Vector2f& position,
		std::string text);

	std::string getText()const;
	void setText(const std::string& text);

	void draw(sf::RenderWindow& window)const;
private:
	sf::Vector2u size_;
	sf::Vector2f position_;
	std::string text_;
};

