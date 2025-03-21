#pragma once

#include "AbstractPoolable.h"
#include "AGameObject.h"
#include "Collider.h"
#include "CollisionListener.h"

class EnemyTorpedo : public AbstractPoolable, public CollisionListener
{
public:
	EnemyTorpedo(std::string name);
	~EnemyTorpedo();
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