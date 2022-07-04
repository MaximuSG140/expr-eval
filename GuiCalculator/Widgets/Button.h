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

	/**
	 * \brief
	 * Checks if mouse is hovered over button and, in such case calls click handler.
	 * \param mouse_position
	 * Mouse position to check.
	 */
	void tryActivate(const sf::Vector2f& mouse_position)const;

	
private:
	/**
	 * \brief
	 * Calculates upper-left corner of centered button label.
	 * \return
	 * Position inside button to print in center.
	 */
	sf::Vector2f getPositionForPrintingCenteredText()const;

	/**
	 * \brief
	 * Checks if mouse is hovered over button
	 * \param mouse_position
	 * Mouse position to check.
	 * \return
	 * True if cursor is on button, false in other case.
	 */
	bool checkoutPosition(const sf::Vector2f& mouse_position)const;

	/**
	 * \brief
	 * Performs on-click action.
	 */
	void onClick()const;

	sf::Vector2f size_;
	sf::Vector2f position_;
	std::function<void()> click_handler_;
	std::string text_;
};

