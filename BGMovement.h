#pragma once

#include "AbstractComponent.h"

class BGMovement : public AbstractComponent
{
public:
    BGMovement(std::string name);
    void perform() override;

private:
    float SPEED_MULTIPLIER = 25.0f;
};
