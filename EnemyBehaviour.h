#pragma once
#include "AbstractComponent.h"

class EnemyBehaviour : public AbstractComponent
{
public:
    EnemyBehaviour(std::string name);
    void perform() override;
    void configure(float delay);
    void reset();
    void setSpeedMultiplier(float multiplier); // Add this method

private:
	const float SPEED_MULTIPLIER = 100.0;
	EnemyBehaviour::EnemyMovementType movementType = Forward;
	float ticks = 0.0f;
	float delay = 0.0f;
	float forwardDuration = 0.0f;
};