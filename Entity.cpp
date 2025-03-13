// Entity.cpp
#include "Entity.h"

Entity::Entity()
{
	// Constructor implementation (if any)
}

void Entity::setTexture(sf::Texture& texture)
{
	mTexture = texture;
	mSprite.setTexture(mTexture);
}

sf::Sprite* Entity::getSprite()
{
	return &mSprite;
}

Entity* Entity::createEntity(sf::Texture* tex, float x, float y)
{
	if (tex == nullptr)
	{
		// Handle the error, e.g., log it or throw an exception
		return nullptr;
	}
	auto entity = new Entity();
	entity->setTexture(*tex);
	entity->mSprite.setPosition(x, y);
	return entity;
}
