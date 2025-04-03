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

	const float MARGIN = 50.0f; // Define the margin value
    sf::Vector2f position = transformable->getPosition();
    if (position.x < MARGIN)
        position.x = MARGIN;
    if (position.x > Game::WINDOW_WIDTH - MARGIN)
        position.x = Game::WINDOW_WIDTH - MARGIN;

    transformable->setPosition(position);

    checkOutOfBounds();
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

void EnemyBehaviour::checkOutOfBounds()
{
    sf::Vector2f position = this->getOwner()->getTransformable()->getPosition();
    if (position.y > Game::WINDOW_HEIGHT)
    {
        GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
        enemyPool->releasePoolable((AbstractPoolable*)this->getOwner());
    }
}