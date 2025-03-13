#pragma once

#include <SFML/Graphics.hpp>
#include "AbstractComponent.h"

class GenericInputController : public AbstractComponent
{
public:
	GenericInputController(std::string name);
	~GenericInputController();

	void perform();
	void assignEvent(sf::Event event);

protected:
	sf::Event event;
};