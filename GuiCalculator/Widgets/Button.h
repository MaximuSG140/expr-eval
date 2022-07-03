#pragma once
#include "pch.h"


/**
 * \brief
 * The button class is arranged to act as simple rectangle button with ability to cause some action on click.
 * Color is sf::Color::Cyan.\n
 * Letter color is sf::Color::Black.
 */
class Button
{
public:
	constexpr static int TEXT_CHARACTER_SIZE = 30;

	/**
	 * \brief
	 * Creates button with specified parameters and attaches click handler to it.
	 * \param size
	 * Initial size of button.
	 * \param position
	 * Initial button position.
	 * \param text
	 * Initial button label.
	 * \param on_click_handler
	 * An functional object, which will be called if user hits button.
	 */
	explicit Button(const sf::Vector2u& size,
	                const sf::Vector2f& position,
	                std::string text,
	                std::function<void()> on_click_handler);

	/**
	 * \brief
	 * Draws button on window.
	 * \param window
	 * Window where button will be drawn.
	 */
	void draw(sf::RenderWindow& window)const;


	void tryActivate(const sf::Vector2f& mouse_position)const;
	bool checkoutPosition(const sf::Vector2f& mouse_position)const;
	void onClick()const;
private:
	sf::Vector2f getPositionForPrintingCenteredText()const;

	sf::Vector2f size_;
	sf::Vector2f position_;
	std::function<void()> click_handler_;
	std::string text_;
};

