#pragma once
#include "AbstractComponent.h"
#include "CollisionListener.h"
#include "AGameObject.h"

class Collider : public AbstractComponent
{
public:
	Collider(std::string name);
	
	void setCollisionListener(CollisionListener* listener);

	void setChecked(bool flag);
	bool isChecked();

	bool willCollide(Collider* other);
	bool alreadyCollided();
	void setAlreadyCollided(bool flag);

	sf::FloatRect getGlobalBounds();
	void setLocalBounds(sf::FloatRect bounds);
	void collisionEnter(AGameObject* gameObject);
	void collisionExit(AGameObject* gameObject);

	void perform();

private:
	bool collided = false;
	bool checked = false;
	sf::FloatRect localBounds;
	CollisionListener* listener;
};