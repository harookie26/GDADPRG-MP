#pragma once
#include "AbstractComponent.h"
#include "AGameObject.h"
#include <unordered_map>
#include <vector>
#include "Collider.h"

typedef std::vector<Collider*> CollisionList;

class PhysicsManager : public AbstractComponent
{
public:
	static void initialize(std::string name, AGameObject* parent);
	static PhysicsManager* getInstance();

	void trackObject(Collider* object);
	void untrackObject(Collider* object);
	void perform();

private:
	PhysicsManager(std::string name) : AbstractComponent(name, AbstractComponent::Script) {};
	PhysicsManager(PhysicsManager const&)  : AbstractComponent(name, AbstractComponent::Script) {};
	PhysicsManager& operator=(PhysicsManager const&) {};
	static PhysicsManager* sharedInstance;

	CollisionList trackedObjects;
	CollisionList forCleaningObjects;

	void cleanUpObjects();
};