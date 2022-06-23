#pragma once
#include <SFML/System/Vector2.hpp>

template<typename I1, typename I2>
sf::Vector2<I1> ConvertFrom(const sf::Vector2<I2>& converting_value)
{
	return { static_cast<I1>(converting_value.x),
		static_cast<I1>(converting_value.y) };
}
