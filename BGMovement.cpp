#include "BGMovement.h"
#include "BGObject.h"
#include "Game.h"

/**
 * @brief Construct a new BGMovement object
 *
 * @param name The name of the component
 */
BGMovement::BGMovement(std::string name)
    : AbstractComponent(name, AbstractComponent::ComponentType::Script), speedFactor(1.0f)
{
}

/**
 * @brief Perform the background movement logic
 *
 * Moves the background sprite downwards by a speed multiplier and resets its position
 * when it reaches a certain point to create a continuous scrolling effect.
 */
void BGMovement::perform()
{
    BGObject* bgObject = (BGObject*)this->getOwner();
    sf::Sprite* sprite = bgObject->getSprite();

    sf::Vector2f offset(0.0f, 0.0f);
    offset.y += SPEED_MULTIPLIER * speedFactor;

    sprite->move(offset * this->deltaTime.asSeconds());

    sf::Vector2f localPos = sprite->getPosition();
    if (localPos.y >= 0)
    {
        sprite->setPosition(0, -Game::WINDOW_HEIGHT * 7);
    }

    // Increment the speed factor over time
    speedFactor += 0.01f * this->deltaTime.asSeconds();
}
