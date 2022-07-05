#pragma once
#include "pch.h"

/**
 * \brief
 * Class edit represents drawable entity,\n
 * which looks like monotonic white rectangle with text inside it.\n
 * Text font is OpenSans-Regular.\n
 * Letter color is sf::Color::Black.
 * Letter size is automatically calculated to match edit's size.
 */
class Edit
{
public:


	/**
	 * \brief
	 * Constructs edit in drawable state.
	 * \param size
	 * Desired size of edit window.
	 * \param position
	 * Desired position of edit in window in which it will be rendered.
	 * \param text
	 * Initial text which edit will contain.
	*/
	explicit Edit(const sf::Vector2u& size,
		const sf::Vector2f& position,
		std::string text);

	/**
	 * \brief
	 * Retrieve text displayed on edit.
	 * \return
	 * String representation of displayed text.
	 */
	std::string getText()const;

	/**
	 * \brief
	 * Assign new text for rendering.\n For changes to become visible window should be flushed.
	 * \param text
	 * New text value for edit.
	 */
	void setText(const std::string& text);

	/**
	 * \brief
	 * Draws edit on specified window.
	 * \param window
	 * Window where edit will be drown.
	 */
	void draw(sf::RenderWindow& window)const;
private:
	/**
	 * \brief
	 * Calculates position for sf::Text where to be printed as if it was vertical centered and aligned to left.
	 * \return
	 * Position for printing sf::Text aligned to left and centered for vertical.
	 */
	sf::Vector2f calculateCenteredTextPosition()const;
	/**
	 * \brief
	 * Calculates optimal letter size to fit the edit.
	 * \return
	 * Optimal text letter size parameter to fit the edit.
	 */
	unsigned calculateOptimalLetterSize()const;

	sf::Vector2u size_;
	sf::Vector2f position_;
	std::string text_;
	sf::Font font_;
};

