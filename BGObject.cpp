#include "BGObject.h"

#include <iostream>

#include "Game.h"
#include "Renderer.h"
#include "TextureManager.h"

/**
 * @brief Construct a new BGObject::BGObject object
 *
 * @param name The name of the background object
 */
BGObject::BGObject(const std::string& name)
    : AGameObject(name), mName(name)
{
}

/**
 * @brief Initialize the background object by setting up the sprite and its texture
 */
void BGObject::initialize()
{
    std::cout << "Declared as " << this->getName() << "\n";

    sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("desert_bg"));
    sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
    sprite->setTextureRect(sf::IntRect(0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT * 8));
    sprite->setPosition(0, -Game::WINDOW_HEIGHT * 7);

	BGMovement* movement = new BGMovement("BGMovement_1");
	this->attachComponent(movement);

	Renderer* renderer = new Renderer("BGRenderer");
	renderer->assignDrawable(this->sprite);
	this->attachComponent(renderer);
}

sf::Sprite* BGObject::getSprite()
{
	return this->sprite;
}

/**
 * @brief Process input events for the background object
 *
 * @param event The event to process
 */
void BGObject::processInput(sf::Event event)
{

}

/**
 * @brief Update the background object's position based on the elapsed time
 *
 * @param deltaTime The time elapsed since the last update
 */
void BGObject::update(sf::Time deltaTime)
{
	AGameObject::update(deltaTime);

    BGMovement* movement = (BGMovement*)(this->getComponentsOfType(AbstractComponent::ComponentType::Script)[0]);
    movement->setDeltaTime(deltaTime);
    movement->perform();
}
