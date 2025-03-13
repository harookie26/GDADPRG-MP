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

void Collider::setChecked(bool flag)
{
	this->checked = flag;
}

bool Collider::isChecked()
{
	return this->checked;
}

bool Collider::willCollide(Collider* other)
{
	sf::FloatRect A = other->getGlobalBounds();
	sf::FloatRect B = this->getGlobalBounds();

	return A.intersects(B);
}

bool Collider::alreadyCollided()
{
	return this->collided;
}

void Collider::setAlreadyCollided(bool flag)
{
	this->collided = flag;
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