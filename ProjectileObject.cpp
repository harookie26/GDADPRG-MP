#include "ProjectileObject.h"
#include "TextureManager.h"
#include "ProjectileMovement.h"
#include "AirplanePlayer.h"
#include "GameObjectManager.h"
#include <string>
#include "ObjectPoolHolder.h"
#include "Renderer.h"
#include "SFXManager.h"
#include <iostream>

ProjectileObject::ProjectileObject(std::string name) : AbstractPoolable(name), CollisionListener()
{
}

void ProjectileObject::initialize()
{
    this->sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("bullet"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
    this->sprite->setScale(2.0f, 2.0f); // Scale the sprite by 2x

    Renderer* renderer = new Renderer("EnemySprite");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);

    this->projectileMovement = new ProjectileMovement("projectile_movement");
    this->attachComponent(this->projectileMovement);

    this->collider = new Collider("ProjectileCollider");
    // Retrieve the global bounds of the sprite
    sf::FloatRect globalBounds = sprite->getGlobalBounds();

    // Scale the bounds to be slightly smaller
    float scaleFactor = 0.1f; // Adjust this value as needed
    sf::FloatRect scaledBounds(
        globalBounds.left + (globalBounds.width * (1 - scaleFactor) / 2),
        globalBounds.top + (globalBounds.height * (1 - scaleFactor) / 2),
        globalBounds.width * scaleFactor,
        globalBounds.height * scaleFactor
    );

    // Set the scaled bounds to the collider
    this->collider->setLocalBounds(scaledBounds);
    this->collider->setCollisionListener(this);
    this->attachComponent(this->collider);

    PhysicsManager::initialize("PhysicsManager", this);
}


void ProjectileObject::onRelease()
{
	PhysicsManager::getInstance()->untrackObject(this->collider);
}

void ProjectileObject::onActivate()
{
	AirplanePlayer* player = (AirplanePlayer*)GameObjectManager::getInstance()->findObjectByName("PlaneObject");
	sf::Vector2f position = player->getTransformable()->getPosition();
	this->setPosition(position.x, position.y);

	this->hasHit = false;
	SFXManager::getInstance()->playSound("firing");
	PhysicsManager::getInstance()->trackObject(this->collider);
}

AbstractPoolable* ProjectileObject::clone()
{
	AbstractPoolable* copyObj = new ProjectileObject(this->name);
	return copyObj;
}

void ProjectileObject::onCollisionEnter(AGameObject* gameObject)
{
	if (gameObject->getName().find("enemy") != std::string::npos && !this->hasHit)
	{
        std::cout << "HIT" << std::endl;

		this->hasHit = true;
		GameObjectPool* projectilePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECTILE_POOL_TAG);
		projectilePool->releasePoolable((AbstractPoolable*)this);
	}
}


void ProjectileObject::onCollisionExit(AGameObject* gameObject)
{
    std::cout << "Projectile " << this->name << " exited collision with " << gameObject->getName() << std::endl;
}