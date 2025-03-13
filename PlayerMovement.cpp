#include "PlayerMovement.h"

#include "AirplanePlayer.h"
#include "ObjectPoolHolder.h"
#include "PlayerInputController.h"

/**
 * @brief Construct a new Player Movement object
 *
 * @param name The name of the component
 */
PlayerMovement::PlayerMovement(std::string name) : AbstractComponent(name, AbstractComponent::ComponentType::Script)
{

}

/**
 * @brief Perform the player movement logic
 *
 * Moves the player based on input from the PlayerInputController.
 */
void PlayerMovement::perform()
{
    AirplanePlayer* airplanePlayer = (AirplanePlayer*)this->getOwner();
    PlayerInputController* inputController = (PlayerInputController*)(airplanePlayer->getComponentsOfType(AbstractComponent::ComponentType::Input)[0]);
    sf::Transformable* playerTransformable = airplanePlayer->getTransformable();

    if (playerTransformable == nullptr || inputController == nullptr)
    {
        std::cout << "playerTransformable not found" << std::endl;
    }

    sf::Vector2f offset(0.0f, 0.0f);

    if (inputController->isUp())
    {
        offset.y -= this->SPEED_MULTIPLIER;
        playerTransformable->move(offset * this->deltaTime.asSeconds());
    }
    else if (inputController->isDown())
    {
        offset.y += this->SPEED_MULTIPLIER;
        playerTransformable->move(offset * this->deltaTime.asSeconds());
    }
    else if (inputController->isLeft())
    {
        offset.x -= this->SPEED_MULTIPLIER;
        playerTransformable->move(offset * this->deltaTime.asSeconds());
    }
    else if (inputController->isRight())
    {
        offset.x += this->SPEED_MULTIPLIER;
        playerTransformable->move(offset * this->deltaTime.asSeconds());
    }

    this->ticks += this->deltaTime.asSeconds();
    if (inputController->hasFired() && this->ticks > this->BULLET_SPAWN_INTERVAL)
    {
        this->projectilePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECTILE_POOL_TAG);
        this->ticks = 0.0f;
        this->projectilePool->requestPoolable();
    }
}
