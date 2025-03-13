#include "UIButtonInputController.h"
#include <string>
#include <iostream>

UIButtonInputController::UIButtonInputController(std::string name, ButtonListener* listener) : GenericInputController(name)
{
	this->buttonListener = listener;
}

UIButtonInputController::~UIButtonInputController()
{
}

void UIButtonInputController::perform()
{
	UIButton* button = (UIButton*)this->getOwner();

	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && this->pressed)
	{
		this->pressed = false;
		button->changeButtonToNormal();
		this->buttonListener->onButtonReleased(button);
	}

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
		sf::FloatRect bounds = button->getGlobalBounds();

		if (bounds.contains(mousePos))
		{
			this->pressed = true;
			button->changeButtonToPressed();
			this->buttonListener->onButtonClick(button);
		}
	}
}