#include "pch.h"

#include "NotificationWindow.h"

NotificationWindow::NotificationWindow(std::string notification_text)
	:window_(sf::VideoMode(WIDTH, HEIGHT), 
	         "Notification",
	         sf::Style::Titlebar | sf::Style::Close),
	close_button_({BUTTON_WIDTH, BUTTON_HEIGHT},
	              {BUTTON_X, BUTTON_Y},
	              "Ok",
	              [&]()
	              {
		              window_.close();
	              }),
	notification_(std::move(notification_text))
{
	window_.requestFocus();
	window_.clear(sf::Color::White);
	sf::String line(notification_.c_str());
	sf::Font font;
	auto success = font.loadFromFile("Fonts/OpenSans-Regular.ttf");
	if (!success)
	{
		throw std::runtime_error("Error loading font");
	}
	sf::Text text(line, font);
	text.setPosition({ 0, 0 });
	text.setFillColor(sf::Color::Black);
	window_.draw(text);
	close_button_.draw(window_);
	window_.display();
}

void NotificationWindow::waitForClose()
{
	sf::Event event{};
	bool left_mouse_button_pressed = false;
	while (window_.isOpen())
	{
		window_.pollEvent(event);
		switch (event.type)
		{
		case sf::Event::Closed:
			window_.close();
			break;
		case sf::Event::MouseButtonReleased:
			if (!left_mouse_button_pressed ||
				event.mouseButton.button != sf::Mouse::Left)
			{
				break;
			}
			close_button_.tryActivate({ static_cast<float>(event.mouseButton.x),
				static_cast<float>(event.mouseButton.y) });
			left_mouse_button_pressed = false;
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button != sf::Mouse::Left)
			{
				break;
			}
			left_mouse_button_pressed = true;
			break;
		default:
			break;
		}
	}
}
