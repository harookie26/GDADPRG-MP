#include "ASMovement.h"
#include "AGameObject.h"

#include <iostream>

AirplaneSupportMovement::AirplaneSupportMovement(std::string name)
	: AbstractComponent(name, AbstractComponent::ComponentType::Script)
{
}

void AirplaneSupportMovement::perform()
{
}