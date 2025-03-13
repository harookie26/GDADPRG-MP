#pragma once
#include "AbstractComponent.h"

class AirplaneSupportMovement : public AbstractComponent
{
public:
	AirplaneSupportMovement(std::string name);
	void perform() override;
	bool moveLeft = false;
	bool moveRight = false;

private:
	const float SPEED = 50.0f;
};