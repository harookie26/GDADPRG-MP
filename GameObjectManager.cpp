#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;


GameObjectManager::GameObjectManager()
{
}

GameObjectManager* GameObjectManager::getInstance()
{
	if (sharedInstance == nullptr)
	{
		sharedInstance = new GameObjectManager();
	}
	return sharedInstance;
}

AGameObject* GameObjectManager::findObjectByName(std::string name)
{
	if (mGameObjectMap.find(name) != mGameObjectMap.end())
	{
		return mGameObjectMap[name];
	}
	else
	{
		std::cerr << "GameObjectManager::findObjectByName: Object with name " << name << " not found." << std::endl;
	}
	return nullptr;
}

std::vector<AGameObject*> GameObjectManager::getAllObjects()
{
	return mGameObjectList;
}

int GameObjectManager::activeObjects()
{
	return mGameObjectList.size();
}

void GameObjectManager::processInput(sf::Event event)
{
	for (int i = 0; i < mGameObjectList.size(); i++)
	{
		mGameObjectList[i]->processInput(event);
	}
}

void GameObjectManager::update(sf::Time deltaTime)
{
	for (int i = 0; i < mGameObjectList.size(); i++)
	{
		mGameObjectList[i]->update(deltaTime);
		for (AbstractComponent* component : mGameObjectList[i]->getComponentsOfType(AbstractComponent::Script))
		{
			component->setDeltaTime(deltaTime);
			component->perform();
		}
	}
}

void GameObjectManager::draw(sf::RenderWindow* targetWindow)
{
	for (int i = 0; i < mGameObjectList.size(); i++)
	{
		mGameObjectList[i]->draw(targetWindow, sf::RenderStates::Default);
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	mGameObjectMap[gameObject->getName()] = gameObject;
	mGameObjectList.push_back(gameObject);
	gameObject->initialize();
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	std::string key = gameObject->getName();
	delete gameObject;
	mGameObjectMap.erase(key);
	mGameObjectList.erase(std::remove(mGameObjectList.begin(), mGameObjectList.end(), gameObject), mGameObjectList.end());
	mGameObjectList.shrink_to_fit();
}

void GameObjectManager::deleteObjectByName(std::string name)
{
	AGameObject* gameObject = findObjectByName(name);
	if (gameObject != nullptr)
	{
		deleteObject(gameObject);
	}
}

void GameObjectManager::deleteAllObjectsInScene()
{
	for (int i = 0; i < mGameObjectList.size(); i++)
	{
		delete this->mGameObjectList[i];
	}

	this->mGameObjectList.clear();
	this->mGameObjectList.shrink_to_fit();
	this->mGameObjectMap.clear();
}