#include "GenericInputController.h"

GenericInputController::GenericInputController(std::string name)
	: AbstractComponent(name, AbstractComponent::ComponentType::Input)
{
	this->type = Input;
}

GenericInputController::~GenericInputController()
{
	AbstractComponent::~AbstractComponent();
}

void GenericInputController::perform()
{
}

void GenericInputController::assignEvent(sf::Event event)
{
	this->event = event;
}