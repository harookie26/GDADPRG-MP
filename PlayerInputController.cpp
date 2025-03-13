#include "PlayerInputController.h"

/**
 * @brief Construct a new Player Input Controller object
 *
 * @param name The name of the input controller
 */
PlayerInputController::PlayerInputController(std::string name)
    : GenericInputController(name)
{
}

/**
 * @brief Destroy the Player Input Controller object
 *
 */
PlayerInputController::~PlayerInputController()
{
    (GenericInputController::~GenericInputController());
}

/**
 * @brief Set the event for the input controller
 *
 * @param event The event to set
 */
void PlayerInputController::setEvent(sf::Event event)
{
    this->event = event;
}

/**
 * @brief Perform the input handling logic
 *
 * Sets the movement flags based on the current event.
 */
void PlayerInputController::perform()
{
    bool keyFlag = false;

    if (event.type == sf::Event::KeyPressed)
    {
        keyFlag = true;
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        keyFlag = false;
    }

    switch (event.key.code)
    {
    case sf::Keyboard::W:
        this->moveUp = keyFlag;
        break;
    case sf::Keyboard::S:
        this->moveDown = keyFlag;
        break;
    case sf::Keyboard::A:
        this->moveLeft = keyFlag;
        break;
    case sf::Keyboard::D:
        this->moveRight = keyFlag;
        break;
	case sf::Keyboard::Space:
		this->fire = keyFlag;
		break;
    }
}

/**
 * @brief Check if the up key is pressed
 *
 * @return true If the up key is pressed
 * @return false If the up key is not pressed
 */
bool PlayerInputController::isUp()
{
    return this->moveUp;
}

/**
 * @brief Check if the down key is pressed
 *
 * @return true If the down key is pressed
 * @return false If the down key is not pressed
 */
bool PlayerInputController::isDown()
{
    return this->moveDown;
}

/**
 * @brief Check if the left key is pressed
 *
 * @return true If the left key is pressed
 * @return false If the left key is not pressed
 */
bool PlayerInputController::isLeft()
{
    return this->moveLeft;
}

/**
 * @brief Check if the right key is pressed
 *
 * @return true If the right key is pressed
 * @return false If the right key is not pressed
 */
bool PlayerInputController::isRight()
{
    return this->moveRight;
}

bool PlayerInputController::hasFired()
{
	return this->fire;
}
