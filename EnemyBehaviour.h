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
    float SPEED_MULTIPLIER = 100.0f;
    float speedMultiplier = 1.0f; // Add this member variable
    float ticks = 0.0f;
    float delay = 0.0f;
    float forwardDuration = 0.0f;
    enum EnemyMovementType { Forward, SlowForward, Side } movementType = Forward;
};
