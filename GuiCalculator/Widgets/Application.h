#pragma once
#include "pch.h"

#include "Button.h"
#include "Edit.h"
#include "Utility/EvaluationHistory.h"

/**
 * \brief
 * Class Application represents one calculator
 * instance, it handles window size and runs event loop,
 * also application makes proper use ot its components such as buttons and edits.
 */
class Application
{
public:
	constexpr static unsigned MINIMAL_POSSIBLE_WINDOW_WIDTH = 500;
	constexpr static unsigned MINIMAL_POSSIBLE_WINDOW_HEIGHT = 500;
	constexpr static int MAX_HISTORY_SIZE = 5;

	/**
	 * \brief
	 * Creates calculator instance with specified window size.
	 * \param window_width
	 * Width of created window. Can't be less than MINIMAL_POSSIBLE_WINDOW_WIDTH.
	 * \param window_height
	 * Height of created window. Can't be less than MINIMAL_POSSIBLE_WINDOW_HEIGHT.
	 */
	explicit Application(unsigned window_width,
	                     unsigned window_height);

	/**
	 * \brief
	 * Enables application ability to receive events from OS and handle them.
	 */
	void run();
private:
	sf::RenderWindow main_window_;
	std::vector<Button> buttons_{};
	Edit expression_field_;
	EvaluationHistory history_{MAX_HISTORY_SIZE};

	/**
	 * \brief
	 * Calculates size of edit where user's expression will show.
	 * \param window_size
	 * Size of window to which edit belongs.
	 * \return
	 * Size of edit to match window size.
	 */
	static sf::Vector2u calculateEditSize(const sf::Vector2u& window_size);

	/**
	 * \brief
	 * Calculates edit's position depending on size of window to which edit belongs.
	 * \param window_size
	 * Size of window which edit belongs to.
	 * \return
	 * Position of edit to match window size.
	 */
	static sf::Vector2f calculateEditPosition(const sf::Vector2u& window_size);

	/**
	 * \brief
	 * Calculates button size depending on window size.\n
	 * All buttons are of the same size for simplicity.
	 * \param window_size
	 * Size of window button will belong to.
	 * \return
	 * Default size of button, which matches specified window size.
	 */
	static sf::Vector2u calculateDefaultButtonSize(const sf::Vector2u& window_size);

	/**
	 * \brief
	 * Calculates button position from upper-left corner of window with specified size.\n
	 * Uses button position in button plate to compute. 
	 * \param window_size
	 * Size of window to which button will belong.
	 * \param button_position
	 * Button offset from upper and left border in "buttons".
	 * \return
	 * Calculated position of button.
	 */
	static sf::Vector2f calculateButtonPosition(const sf::Vector2u& window_size,
	                                            const sf::Vector2f& button_position);

	/**
	 * \brief
	 * Sets new window size or sets minimal possible size if new size is too little.\n
	 * Size components are treated independently, so if only height/width are not large enough
	 * then height/width will be set to minimum, but width/height will set as user wanted.
	 * \param size
	 * Desired size of window.
	 */
	void setWindowSize(const sf::Vector2u& size);

	/**
	 * \brief
	 * Draws all UI components from scratch.
	 */
	void redrawWindow();

	/**
	 * \brief
	 * Runs event loop to interact with user through sf::Event system.
	 */
	void runEventLoop();

	/**
	 * \brief
	 * Maps keyboard character to specific ASCII symbol.
	 * \param event
	 * Keyboard event to determine symbol from.
	 * \return
	 * Returns corresponding symbol.\n
	 * If symbol is not digit or brake, or arithmetic sign, returns zero character.
	 */
	static char getCharacterPressed(const sf::Event::KeyEvent& event);

	/**
	 * \brief
	 * Notifies user about error in another window and prints message in that window.\n
	 * Method returns control when notification window closed.
	 * \param what
	 * Text that will be printed on new window.
	 */
	static void notifyUser(const std::string& what);

	/**
	 * \brief
	 * Uses evaluation library to compute expression
	 * printed on edit and then prints this value on edit, replacing old expression.
	 */
	void evaluateInput();

	/**
	 * \brief
	 * Fills internal storage with buttons which usually appear in calculator.
	 * \
	 * Button map:\n
	 * ___________\n
	 * |7 8 9 + =|\n
	 * |4 5 6 - <|\n
	 * |1 2 3 * C|\n
	 * |( ) 0 / ^|\n
	 * |_________|\n
	 */
	void initializeButtons();
};

