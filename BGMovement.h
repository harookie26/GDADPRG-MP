#pragma once

#include "AbstractComponent.h"

class BGMovement : public AbstractComponent
{
public:
    BGMovement(std::string name);
    void perform() override;

private:
    const float SPEED_MULTIPLIER = 100.0f;
};
