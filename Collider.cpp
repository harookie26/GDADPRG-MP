#include "Collider.h"
#include "AGameObject.h"
#include "PhysicsManager.h"
#include <iostream>

Collider::Collider(std::string name) : AbstractComponent(name, AbstractComponent::Physics)
{
}

void Collider::setCollisionListener(CollisionListener* listener)
{
	this->listener = listener;
}

bool Collider::willCollide(Collider* other)
{
	sf::FloatRect A = other->getGlobalBounds();
	sf::FloatRect B = this->getGlobalBounds();

	return A.intersects(B);
}


void Collider::setLocalBounds(sf::FloatRect bounds)
{
	this->localBounds = bounds;
}

void Collider::collisionEnter(AGameObject* gameObject)
{
	if (this->listener != nullptr)
	{
		this->listener->onCollisionEnter(gameObject);
	}
}

void Collider::collisionExit(AGameObject* gameObject)
{
	if (this->listener != nullptr)
	{
		this->listener->onCollisionExit(gameObject);
	}
}

sf::FloatRect Collider::getGlobalBounds()
{
	return this->owner->getGlobalTransform().transformRect(this->localBounds);
}

void Collider::perform()
{

}

bool Collider::hasCollisionWith(Collider* collider)
{
	return this->collisions.find(collider) != this->collisions.end();
}

void Collider::addCollision(Collider* collider)
{
	this->collisions.insert(collider);
}

void Collider::removeCollision(Collider* collider)
{
	this->collisions.erase(collider);
}

void Collider::clearCollisions()
{
	for (Collider* collider : this->collisions)
	{
		collider->collisionExit(this->getOwner());
		this->collisionExit(collider->getOwner());
		collider->removeCollision(this);
	}

	collisions.clear();
}

