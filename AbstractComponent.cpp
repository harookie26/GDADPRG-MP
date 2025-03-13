#include "AbstractComponent.h"

/**
 * @brief Construct a new Abstract Component object
 *
 * @param name The name of the component
 * @param type The type of the component
 */
AbstractComponent::AbstractComponent(std::string name, ComponentType type)
{
	this->name = name;
	this->owner = nullptr;
	this->type = type;
}

/**
 * @brief Destroy the Abstract Component object
 *
 */
AbstractComponent::~AbstractComponent()
{
	this->owner = nullptr;
	this->type = ComponentType::NotSet;
}

/**
 * @brief Get the owner of the component
 *
 * @return AGameObject* Pointer to the owner game object
 */
AGameObject* AbstractComponent::getOwner()
{
	return this->owner;
}

/**
 * @brief Get the type of the component
 *
 * @return AbstractComponent::ComponentType The type of the component
 */
AbstractComponent::ComponentType AbstractComponent::getType()
{
	return this->type;
}

/**
 * @brief Get the name of the component
 *
 * @return std::string The name of the component
 */
std::string AbstractComponent::getName()
{
	return this->name;
}

/**
 * @brief Set the delta time for the component
 *
 * @param deltaTime The delta time to set
 */
void AbstractComponent::setDeltaTime(sf::Time deltaTime)
{
	this->deltaTime = deltaTime;
}

/**
 * @brief Attach an owner game object to the component
 *
 * @param object Pointer to the game object to attach
 */
void AbstractComponent::attachOwner(AGameObject* object)
{
	this->owner = object;
}

/**
 * @brief Detach the owner game object from the component
 *
 */
void AbstractComponent::detachOwner()
{
	delete this;
}
