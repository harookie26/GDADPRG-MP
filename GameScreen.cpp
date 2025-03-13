#include "GameScreen.h"
#include "TextureManager.h"
#include "Game.h"

#include <iostream>
#include <string>

#include "AirplanePlayer.h"
#include "AirplaneSupport.h"
#include "ApplicationManager.h"
#include "BGObject.h"
#include "EmptyGameObject.h"
#include "EnemySwarmHandler.h"
#include "GameObjectManager.h"
#include "ObjectPoolHolder.h"
#include "ProjectileObject.h"
#include "QuitButton.h"
#include "SceneManager.h"
#include "UIButton.h"
#include "UIText.h"

GameScreen::GameScreen(std::string name) : AGameObject(name), ButtonListener()
{
}

void GameScreen::initialize()
{
    ApplicationManager::getInstance()->setState(ApplicationManager::Running);

    BGObject* bgObject = new BGObject("BGObject");
    GameObjectManager::getInstance()->addObject(bgObject);

    AirplanePlayer* planeObject = new AirplanePlayer("PlaneObject");
    GameObjectManager::getInstance()->addObject(planeObject);

    AirplaneSupport* support1 = new AirplaneSupport("AirSupport_1", true);
    planeObject->attachChild(support1);
    support1->setPosition(50, 100);

    AirplaneSupport* support2 = new AirplaneSupport("AirSupport_2", false);
    planeObject->attachChild(support2);
    support2->setPosition(-50, 100);

    srand(time(nullptr));
    EmptyGameObject* enemiesManager = new EmptyGameObject("EnemiesManager");
    EnemySwarmHandler* swarmHandler = new EnemySwarmHandler(200, "SwarmHandler", enemiesManager);
    enemiesManager->attachComponent(swarmHandler);
    GameObjectManager::getInstance()->addObject(enemiesManager);

    GameObjectPool* projectilePool = new GameObjectPool(ObjectPoolHolder::PROJECTILE_POOL_TAG, new ProjectileObject("projectile"), 10, nullptr);
    projectilePool->initialize();
    ObjectPoolHolder::getInstance()->registerObjectPool(projectilePool);

    QuitButton* PauseMenu = new QuitButton("PauseMenu");
    GameObjectManager::getInstance()->addObject(PauseMenu);
}

void GameScreen::onButtonClick(UIButton* button)
{
    /*std::cout << button->getName();*/
}

void GameScreen::onButtonReleased(UIButton* button)
{
    std::cout << button->getName();
}

void GameScreen::registerObject(AGameObject* object)
{
    GameObjectManager::getInstance()->addObject(object);
}
