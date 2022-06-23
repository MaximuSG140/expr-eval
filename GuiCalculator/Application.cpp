#include "Application.h"
#include "Evaluate.h"
#include "Utility.h"

Application::Application(const unsigned window_width,
                         const unsigned window_height)
	:main_window_(sf::VideoMode(std::max(window_width, MINIMAL_POSSIBLE_WINDOW_WIDTH),
			std::max(window_height, MINIMAL_POSSIBLE_WINDOW_HEIGHT)),
		"Calculator"),
		expression_field_(calculateEditSize(main_window_.getSize()),
		calculateEditPosition(main_window_.getSize()),
		"")
{
	initializeButtons();
	main_window_.setKeyRepeatEnabled(false);
	redrawWindow();
}

void Application::run()
{
	runEventLoop();
}

sf::Vector2u Application::calculateEditSize(const sf::Vector2u& window_size)
{
	return { window_size.x, window_size.y / 4 };
}

sf::Vector2f Application::calculateEditPosition(const sf::Vector2u& window_size)
{
	return { 0, 0 };
}

sf::Vector2u Application::calculateDefaultButtonSize(const sf::Vector2u& window_size)
{
	auto edit_size = calculateEditSize(window_size);
	auto edit_position = calculateEditPosition(window_size);
	return { window_size.x / 5,
		static_cast<unsigned>((window_size.y - edit_position.y - edit_size.y) / 4 )};
}

sf::Vector2f Application::calculateButtonPosition(const sf::Vector2u& window_size,
	const sf::Vector2f& button_position)
{
	auto button_size = calculateDefaultButtonSize(window_size);
	auto edit_size = calculateEditSize(window_size);
	auto edit_position = calculateEditPosition(window_size);
	return { button_position.x * button_size.x,
		edit_position.y + edit_size.y + button_size.y * button_position.y };
}

void Application::setWindowSize(const sf::Vector2u& size)
{
	sf::Vector2u new_size{ std::max(size.x, MINIMAL_POSSIBLE_WINDOW_WIDTH),
		std::max(size.y, MINIMAL_POSSIBLE_WINDOW_HEIGHT) };
	main_window_.setSize(new_size);
}

void Application::redrawWindow()
{
	main_window_.clear({ 200, 200, 200 });
	for(const auto& button : buttons_)
	{
		button.draw(main_window_);
	}
	expression_field_.draw(main_window_);
	main_window_.display();
}

void Application::runEventLoop()
{
	sf::Event event;
	bool left_mouse_button_pressed = false;
	while (main_window_.isOpen())
	{
		main_window_.pollEvent(event);
		switch (event.type)
		{
		case sf::Event::Closed:
			main_window_.close();
			break;
		case sf::Event::MouseButtonReleased:
			if(!left_mouse_button_pressed || 
				event.mouseButton.button != sf::Mouse::Left)
			{
				break;
			}
			for (auto& button : buttons_)
			{
				button.tryActivate({ static_cast<float>(event.mouseButton.x),
					static_cast<float>(event.mouseButton.y) });
			}
			left_mouse_button_pressed = false;
			redrawWindow();
			break;
		case sf::Event::MouseButtonPressed:
			if(event.mouseButton.button != sf::Mouse::Left)
			{
				break;
			}
			left_mouse_button_pressed = true;
			break;
		case sf::Event::Resized:
			setWindowSize({event.size.width,
				event.size.height});
			redrawWindow();
			break;
		case sf::Event::KeyPressed:
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
			{
				auto character = getCharacterPressed(event.key);
				auto expression = expression_field_.getText();
				expression.push_back(character);
				expression_field_.setText(expression);
				redrawWindow();
			}
			else
			{
				evaluateInput();
				redrawWindow();
			}
			break;
		default:;
		}
	}
}

char Application::getCharacterPressed(const sf::Event::KeyEvent& event)
{
	switch(event.code)
	{
	case sf::Keyboard::Num0:
		return '0';
	case sf::Keyboard::Num1:
		return '1';
	case sf::Keyboard::Num2:
		return '2';
	case sf::Keyboard::Num3:
		return '3';
	case sf::Keyboard::Num4: 
		return '4';
	case sf::Keyboard::Num5: 
		return '5';
	case sf::Keyboard::Num6:
		return '6';
	case sf::Keyboard::Num7:
		return '7';
	case sf::Keyboard::Num8:
		return '8';
	case sf::Keyboard::Num9:
		return '9';
	case sf::Keyboard::Slash:
		return '/';
	case sf::Keyboard::Dash:
		return '-';
	case sf::Keyboard::Add:
		return '+';
	case sf::Keyboard::Subtract:
		return '-';
	case sf::Keyboard::Multiply:
		return '*';
	case sf::Keyboard::Divide:
		return '/';
	case sf::Keyboard::Numpad0:
		return '0';
	case sf::Keyboard::Numpad1:
		return '1';
	case sf::Keyboard::Numpad2:
		return '2';
	case sf::Keyboard::Numpad3:
		return '3';
	case sf::Keyboard::Numpad4:
		return '4';
	case sf::Keyboard::Numpad5:
		return '5';
	case sf::Keyboard::Numpad6:
		return '6';
	case sf::Keyboard::Numpad7:
		return '7';
	case sf::Keyboard::Numpad8:
		return '8';
	case sf::Keyboard::Numpad9:
		return '9';
	default: 
		return '\0';
	}
}

void Application::evaluateInput()
{
	auto expression = expression_field_.getText();
	auto result = std::to_string(Evaluate(expression));
	expression_field_.setText(result);
}

void Application::initializeButtons()
{
	buttons_.reserve(20);
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 0,0 }),
		"7",
		[&]()
		{
			auto expression = expression_field_.getText();
			expression.push_back('7');
			expression_field_.setText(expression);
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 1,0 }),
		"8",
		[&]()
		{
			auto expression = expression_field_.getText();
			expression.push_back('8');
			expression_field_.setText(expression);
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 2,0 }),
		"9",
		[&]()
		{
			auto expression = expression_field_.getText();
			expression.push_back('9');
			expression_field_.setText(expression);
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 0,1 }),
		"4",
		[&]()
		{
			auto expression = expression_field_.getText();
			expression.push_back('4');
			expression_field_.setText(expression);
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 1,1 }),
		"5",
		[&]()
		{
			auto expression = expression_field_.getText();
			expression.push_back('5');
			expression_field_.setText(expression);
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 2,1 }),
		"6",
		[&]()
		{
			auto expression = expression_field_.getText();
			expression.push_back('6');
			expression_field_.setText(expression);
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 0,2 }),
		"1",
		[&]()
		{
			auto expression = expression_field_.getText();
			expression.push_back('1');
			expression_field_.setText(expression);
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 1,2 }),
		"2",
		[&]()
		{
			auto expression = expression_field_.getText();
			expression.push_back('2');
			expression_field_.setText(expression);
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 2,2 }),
		"3",
		[&]()
		{
			auto expression = expression_field_.getText();
			expression.push_back('3');
			expression_field_.setText(expression);
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 3,0 }),
		"+",
		[&]()
		{
			auto expression = expression_field_.getText();
			expression.push_back('+');
			expression_field_.setText(expression);
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 3,1 }),
		"-",
		[&]()
		{
			auto expression = expression_field_.getText();
			expression.push_back('-');
			expression_field_.setText(expression);
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 3,2 }),
		"*",
		[&]()
		{
			auto expression = expression_field_.getText();
			expression.push_back('*');
			expression_field_.setText(expression);
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 0,3 }),
		"(",
		[&]()
		{
			auto expression = expression_field_.getText();
			expression.push_back('(');
			expression_field_.setText(expression);
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 1,3 }),
		")",
		[&]()
		{
			auto expression = expression_field_.getText();
			expression.push_back(')');
			expression_field_.setText(expression);
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 2,3 }),
		"0",
		[&]()
		{
			auto expression = expression_field_.getText();
			expression.push_back('0');
			expression_field_.setText(expression);
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 4,0 }),
		"=",
		[&]()
		{
			evaluateInput();
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 4,1 }),
		"<-",
		[&]()
		{
			auto expression = expression_field_.getText();
			if(!expression.empty())
			{
				expression.pop_back();
			}
			expression_field_.setText(expression);
		});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 4,2 }),
		"C",
		[&]()
	{
		auto expression = expression_field_.getText();
		expression.clear();
		expression_field_.setText(expression);
	});
	buttons_.emplace_back(calculateDefaultButtonSize(main_window_.getSize()),
		calculateButtonPosition(main_window_.getSize(),
			{ 3,3 }),
		"/",
		[&]()
	{
		auto expression = expression_field_.getText();
		expression.push_back('/');
		expression_field_.setText(expression);
	});
}
