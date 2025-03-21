#include "EnemyBehaviour.h"
#include "AGameObject.h"
#include "Game.h"
#include "SpeedManager.h"
#include <SFML/Graphics.hpp>
#include "ObjectPoolHolder.h"

EnemyBehaviour::EnemyBehaviour(std::string name) : AbstractComponent(name, Script)
{
    this->reset();
}

void EnemyBehaviour::perform()
{
    this->ticks += this->deltaTime.asSeconds();
    sf::Transformable* transformable = this->getOwner()->getTransformable();
    float globalSpeedMultiplier = SpeedManager::getInstance()->getSpeedMultiplier();

    if (this->movementType == Forward)
    {
        transformable->move(0, this->deltaTime.asSeconds() * SPEED_MULTIPLIER * speedMultiplier * globalSpeedMultiplier);
    }
    else if (this->movementType == SlowForward)
    {
        transformable->move(0, this->deltaTime.asSeconds() * (SPEED_MULTIPLIER / 2) * speedMultiplier * globalSpeedMultiplier);
    }
    else if (this->movementType == Side)
    {
        transformable->move(0, this->deltaTime.asSeconds() * SPEED_MULTIPLIER * speedMultiplier * globalSpeedMultiplier);
    }
}

void EnemyBehaviour::configure(float delay)
{
    this->delay = delay;
}

void EnemyBehaviour::reset()
{
    this->ticks = 0.0f;
    this->movementType = Forward;
    this->forwardDuration = (rand() % 3) + 1.0f;
}

void EnemyBehaviour::setSpeedMultiplier(float multiplier)
{
    this->speedMultiplier = multiplier;
}
