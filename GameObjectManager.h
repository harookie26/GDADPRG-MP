#pragma once

#include <unordered_map>

#include "AGameObject.h"
#include <vector>
#include <iostream>

class GameObjectManager
{
public:
	static GameObjectManager* getInstance();
	AGameObject* findObjectByName(std::string name);
	std::vector<AGameObject*> getAllObjects();

	int activeObjects();

	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* targetWindow);
	void addObject(AGameObject* object);
	void deleteObject(AGameObject* object);
	void deleteObjectByName(std::string name);
	void deleteAllObjectsInScene();

private:
	GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};

	static GameObjectManager* sharedInstance;

	std::unordered_map<std::string, AGameObject*> mGameObjectMap;
	std::vector<AGameObject*> mGameObjectList;
};