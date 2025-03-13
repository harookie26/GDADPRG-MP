	#include "AirplaneSupport.h"

#include <iostream>

#include "Game.h"
#include "Renderer.h"

/**
 * @brief Construct a new Airplane Support object
 *
 * @param name The name of the airplane support
 * @param startMovingRight Initial direction of movement
 */
AirplaneSupport::AirplaneSupport(std::string name, bool startMovingRight) : AGameObject(name), movingRight(startMovingRight)
{
}

/**
 * @brief Initialize the airplane support object
 *
 * This method sets up the sprite, texture, and initial position of the airplane support.
 */
void AirplaneSupport::initialize()
{
    std::cout << "Declared as " << this->getName() << std::endl;
    this->sprite = new sf::Sprite();
    this->sprite->setTexture(*TextureManager::getInstance()->getTexture("raptor"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
    sprite->setPosition(0, 0);
    this->originalPosition = sprite->getPosition();

	AirplaneSupportMovement* logicComponent = new AirplaneSupportMovement("AirplaneSupportMovement_1");
	this->attachComponent(logicComponent);

    Renderer* renderer = new Renderer("SupportRenderer");
    renderer->assignDrawable(this->sprite);
    this->attachComponent(renderer);
}

/**
 * @brief Process input events for the airplane support
 *
 * @param event The SFML event to process
 *
 * This method is currently empty as the airplane support does not process input.
 */
void AirplaneSupport::processInput(sf::Event event)
{
}

/**
 * @brief Update the airplane support's state
 *
 * @param deltaTime The time elapsed since the last update
 *
 * This method updates the position of the airplane support based on the movement direction and delta time.
 */
void AirplaneSupport::update(sf::Time deltaTime)
{
    float moveDistance = 100.0f;
    sf::Vector2f offset;

    if (movingRight)
    {
        offset = sf::Vector2f(-moveDistance, 0.0f);
    }
    else
    {
        offset = sf::Vector2f(moveDistance, 0.0f);
    }

    sprite->move(offset * deltaTime.asSeconds());
    sf::Vector2f localPos = sprite->getPosition();

    if (movingRight && localPos.x <= moveDistance / -2)
    {
        movingRight = false;
    }
    else if (!movingRight && localPos.x >= moveDistance / 2)
    {
        movingRight = true;
    }
}