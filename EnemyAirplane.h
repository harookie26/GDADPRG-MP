#pragma once

#include "AbstractPoolable.h"
#include "AGameObject.h"
#include "Collider.h"
#include "CollisionListener.h"

class EnemyAirplane : public AbstractPoolable, public CollisionListener
{
public:
	EnemyAirplane(std::string name);
	~EnemyAirplane();
	void initialize() override;

	void onRelease() override;
	void onActivate() override;
	AbstractPoolable* clone() override;

	void onCollisionEnter(AGameObject* gameObject);
	void onCollisionExit(AGameObject* gameObject);

private:
	sf::Sprite* sprite = new sf::Sprite();
	int counter = 0;

	const int SPAWN_RANGE = 300;

	Collider* collider;
};