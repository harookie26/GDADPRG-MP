#include "AirplanePlayer.h"
#include "AirplaneSupport.h"
#include "PhysicsManager.h"
#include "PlayerInputController.h"
#include "PlayerMovement.h"
#include "Renderer.h"

/**
 * @brief Construct a new Airplane Player object
 *
 * @param name The name of the airplane player
 */
AirplanePlayer::AirplanePlayer(std::string name) : AGameObject(name), CollisionListener(), collider(nullptr)
{
}

/**
 * @brief Initialize the airplane player object
 *
 * This method sets up the sprite, texture, and initial position of the airplane player.
 */
void AirplanePlayer::initialize()
{
    std::cout << "Declared as " << this->getName() << std::endl;

    this->sprite = new sf::Sprite();
    this->sprite->setTexture(*TextureManager::getInstance()->getTexture("eagle"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
    this->sprite->setScale(2.0f, 2.0f); // Scale the sprite by 2x
    this->transformable.setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2 + 120);

    PlayerInputController* inputController = new PlayerInputController("MyPlayerInpt");
    this->attachComponent(inputController);

    PlayerMovement* movement = new PlayerMovement("MyMovement");
    this->attachComponent(movement);

    Renderer* renderer = new Renderer("PlayerRenderer");
    renderer->assignDrawable(this->sprite);
    this->attachComponent(renderer);

    this->collider = new Collider("PlayerCollider");

    // Retrieve the global bounds of the sprite
    sf::FloatRect globalBounds = sprite->getGlobalBounds();

    // Scale the bounds to be slightly smaller
    float scaleFactor = 0.3f; // Adjust this value as needed
    sf::FloatRect scaledBounds(
        globalBounds.left + (globalBounds.width * (1 - scaleFactor) / 2),
        globalBounds.top + (globalBounds.height * (1 - scaleFactor) / 2),
        globalBounds.width * (scaleFactor + 0.2f),
        globalBounds.height * scaleFactor
    );

    // Set the scaled bounds to the collider
    this->collider->setLocalBounds(scaledBounds);
    this->collider->setCollisionListener(this);
    this->attachComponent(this->collider);

    // Initialize heart sprites
    for (int i = 0; i < lives; ++i)
    {
        sf::Sprite* heart = new sf::Sprite();
        heart->setTexture(*TextureManager::getInstance()->getTexture("heart")); // Assign the texture
        heart->setTextureRect(sf::IntRect(0 * 1502, 0, 410, 353)); // Crop the sprite
		heart->setScale(0.1f, 0.1f); // Scale the sprite


        heart->setPosition(10 + i * 40, 10); // Position hearts at the upper left
        heartSprites.push_back(heart);
    }
}

/**
 * @brief Process input events for the airplane player
 *
 * @param event The SFML event to process
 *
 * This method updates the movement flags based on keyboard input.
 */
void AirplanePlayer::processInput(sf::Event event)
{
    PlayerInputController* inputController = (PlayerInputController*)(this->getComponentsOfType(AbstractComponent::ComponentType::Input)[0]);
    inputController->setEvent(event);
    inputController->perform(); // Ensure perform is called to update movement flags
}

sf::Transformable* AirplanePlayer::getTransformable()
{
    return &this->transformable;
}

sf::Drawable* AirplanePlayer::getSprite()
{
    return this->sprite;
}

/**
 * @brief Update the airplane player's state
 *
 * @param deltaTime The time elapsed since the last update
 *
 * This method updates the position of the airplane player based on the movement flags and delta time.
 */
void AirplanePlayer::update(sf::Time deltaTime)
{
    AGameObject::update(deltaTime);

    const float MARGIN = 50.0f;
    sf::Vector2f position = this->transformable.getPosition();
    if (position.x < MARGIN)
        position.x = MARGIN;
    if (position.x > Game::WINDOW_WIDTH - MARGIN)
        position.x = Game::WINDOW_WIDTH - MARGIN;
    if (position.y < MARGIN)
        position.y = MARGIN;
    if (position.y > Game::WINDOW_HEIGHT - MARGIN)
        position.y = Game::WINDOW_HEIGHT - MARGIN;

    this->transformable.setPosition(position);
}

/**
 * @brief Reduce the player's lives by one
 */
void AirplanePlayer::takeDamage()
{
    if (lives > 0)
    {
        --lives;
        delete heartSprites.back();
        heartSprites.pop_back();
    }
}

void AirplanePlayer::onCollisionEnter(AGameObject* gameObject)
{
    if (gameObject->getName().find("enemy") != std::string::npos)
    {
        std::cout << "Enemey hit" << std::endl;
        this->takeDamage();
    }
}


void AirplanePlayer::onCollisionExit(AGameObject* gameObject)
{
    std::cout << "Player " << this->name << " exited collision with " << gameObject->getName() << std::endl;
}

int AirplanePlayer::getLives() {
	return lives;

}