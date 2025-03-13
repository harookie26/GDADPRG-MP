#pragma once

#include "AGameObject.h"
#include "BGMovement.h"

class BGObject : public AGameObject
{
public:
    BGObject(const std::string& name);
    void initialize();
    void processInput(sf::Event event) override;
    void update(sf::Time deltaTime) override;
    sf::Sprite* getSprite();

private:
    std::string mName;
    const float SPEED_MULTIPLIER = 100.0f;
    BGMovement* movement;
};
