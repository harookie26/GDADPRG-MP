#include "EnemyBehaviour.h"
#include "AGameObject.h"
#include "Game.h"

#include <SFML/Graphics.hpp>

#include "ObjectPoolHolder.h"

/**
 * @brief Construct a new EnemyBehaviour object
 *
 * @param name The name of the component
 */
EnemyBehaviour::EnemyBehaviour(std::string name) : AbstractComponent(name, Script)
{
    this->reset();
}

/**
 * @brief Perform the enemy behavior logic
 *
 */
void EnemyBehaviour::perform()
{
    this->ticks += this->deltaTime.asSeconds();
    sf::Transformable* transformable = this->getOwner()->getTransformable();
    
	//increment speed multiplier adjust as necessary
    SPEED_MULTIPLIER += 1.0f;
    
    /*if (this->ticks > this->forwardDuration && this->movementType != Side)
    {
        int counter = (this->movementType + 1) % EnemyMovementType::Forward+ 1;
        this->movementType = (EnemyMovementType)counter;
    }*/

    if (this->movementType == Forward)
    {
        transformable->move(0, this->deltaTime.asSeconds() * SPEED_MULTIPLIER);
    }
    else if (this->movementType == SlowForward)
    {
        transformable->move(0, this->deltaTime.asSeconds() * (SPEED_MULTIPLIER / 2));
    }
    else if (this->movementType == Side)
    {
        /*if (transformable->getPosition().x > Game::WINDOW_WIDTH / 2)
        {
            transformable->move(this->deltaTime.asSeconds() * SPEED_MULTIPLIER * 1.5, 0);
        }
        else
        {
            transformable->move(-this->deltaTime.asSeconds() * SPEED_MULTIPLIER * 1.5, 0);
        }

        if (transformable->getPosition().x > Game::WINDOW_WIDTH + 20 || transformable->getPosition().x < -20)
        {
            ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG)->releasePoolable((AbstractPoolable*)this->getOwner());
        }*/
        transformable->move(0, this->deltaTime.asSeconds() * SPEED_MULTIPLIER);
    }

	
	//std::cout << SPEED_MULTIPLIER << std::endl;
}

/**
 * @brief Configure the enemy behavior with a delay
 *
 * @param delay The delay before the behavior starts
 */
void EnemyBehaviour::configure(float delay)
{
    this->delay = delay;
}

/**
 * @brief Reset the enemy behavior to its initial state
 *
 */
void EnemyBehaviour::reset()
{
    this->ticks = 0.0f;
    this->movementType = Forward;
    this->forwardDuration = (rand() % 3) + 1.0f;
}