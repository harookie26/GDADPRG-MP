#pragma once
#include <unordered_map>
#include <unordered_set>

#include "AbstractComponent.h"
#include "CollisionListener.h"
#include "AGameObject.h"

class Collider : public AbstractComponent
{
public:
	Collider(std::string name);
	
	void setCollisionListener(CollisionListener* listener);

	bool willCollide(Collider* other);
	bool hasCollisionWith(Collider* collider);
	void addCollision(Collider* collider);
	void removeCollision(Collider* collider);

	sf::FloatRect getGlobalBounds();
	void setLocalBounds(sf::FloatRect bounds);
	void collisionEnter(AGameObject* gameObject);
	void collisionExit(AGameObject* gameObject);

	void perform();
	void clearCollisions();

private:
	std::unordered_set<Collider*> collisions;

	bool checked = false;
	sf::FloatRect localBounds;
	CollisionListener* listener;
};