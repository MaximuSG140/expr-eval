#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Edit.h"

class Application
{
public:
	constexpr static unsigned MINIMAL_POSSIBLE_WINDOW_WIDTH = 500;
	constexpr static unsigned MINIMAL_POSSIBLE_WINDOW_HEIGHT = 500;

	explicit Application(unsigned window_width,
		unsigned window_height);
	void run();
private:
	sf::RenderWindow main_window_;
	std::vector<Button> buttons_;
	Edit expression_field_;
	static sf::Vector2u calculateEditSize(const sf::Vector2u& window_size);
	static sf::Vector2f calculateEditPosition(const sf::Vector2u& window_size);
	static sf::Vector2u calculateDefaultButtonSize(const sf::Vector2u& window_size);
	static sf::Vector2f calculateButtonPosition(const sf::Vector2u& window_size,
		const sf::Vector2f& button_position);
	void setWindowSize(const sf::Vector2u& size);
	void redrawWindow();
	void runEventLoop();
	static char getCharacterPressed(const sf::Event::KeyEvent& event);
	void evaluateInput();
	void initializeButtons();
};

