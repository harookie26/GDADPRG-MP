#pragma once
#include "AGameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "ASMovement.h"

#include <iostream>

class AirplaneSupport : public AGameObject
{
public:
    AirplaneSupport(std::string name, bool startMovingRight);
    void initialize();
    void processInput(sf::Event event) override;
    void update(sf::Time deltaTime) override;

private:
    const float SPEED_MULTIPLIER = 100.0f;
    bool movingRight;
    sf::Vector2f originalPosition;
};
