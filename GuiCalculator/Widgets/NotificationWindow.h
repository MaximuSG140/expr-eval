#pragma once
#include "pch.h"

#include "Button.h"

class NotificationWindow
{
public:
	constexpr static unsigned WIDTH = 400;
	constexpr static unsigned HEIGHT = 300;
	constexpr static unsigned BUTTON_WIDTH = 100;
	constexpr static unsigned BUTTON_HEIGHT = 75;
	constexpr static float BUTTON_X = WIDTH / 2 - BUTTON_WIDTH / 2;
	constexpr static float BUTTON_Y = 150;

	explicit NotificationWindow(std::string notification_text);
	void waitForClose();
	
private:
	sf::RenderWindow window_;
	Button close_button_;
	std::string notification_;
};

