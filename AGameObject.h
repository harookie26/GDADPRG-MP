#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "AbstractComponent.h"

class AGameObject
{
public:
	AGameObject(std::string name);

	virtual ~AGameObject();
	virtual void initialize() = 0;
	virtual void processInput(sf::Event event);
	virtual void update(sf::Time deltaTime);
	virtual void draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates);
	sf::Transformable* getTransformable();

	std::string getName();

	void attachChild(AGameObject* child);
	void detachChild(AGameObject* child);
	void setPosition(float x, float y);

	void attachComponent(AbstractComponent* component);
	void detachComponent(AbstractComponent* component);
	AbstractComponent* findComponentByName(std::string name);
	AbstractComponent* findComponentOfType(AbstractComponent::ComponentType type, std::string name);
	std::vector<AbstractComponent*> getComponentsOfType(AbstractComponent::ComponentType type);

	void setEnabled(bool flag);
	bool isEnabled();

	AGameObject* getParent();
	sf::Transform getGlobalTransform();

protected:
	void setParent(AGameObject* gameObject);

	sf::Transformable transformable;
	std::string name;
	sf::Sprite* sprite;
	sf::Texture* texture;
	std::vector<AGameObject*> childList;
	std::vector<AbstractComponent*> componentList;

private:
	AGameObject* mParent;
	std::vector<AbstractComponent*> getComponentsRecursiveProper(AGameObject* object, AbstractComponent::ComponentType type, std::vector<AbstractComponent*> foundList);
	bool enabled = true;
};
