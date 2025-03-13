#pragma once
#include "AbstractComponent.h"
#include "AbstractPoolable.h"
#include "ProjectileMovement.h"
#include "PhysicsManager.h"

class ProjectileObject : public AbstractPoolable, public CollisionListener
{
public:
	ProjectileObject(std::string name);
	void initialize();
	void onRelease();
	void onActivate();
	AbstractPoolable* clone();

	void onCollisionEnter(AGameObject* gameObject);
	void onCollisionExit(AGameObject* gameObject);

private:
	ProjectileMovement* projectileMovement = nullptr;
	Collider* collider = nullptr;
	bool hasHit = false;
};