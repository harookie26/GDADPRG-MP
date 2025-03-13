#include "GameScene.h"

#include "GameScreen.h"


GameScene::GameScene()
    : AbstractScene("GameScene")
{
}

void GameScene::onLoadResources()
{
    // Load resources specific to the game scene here
}

void GameScene::onLoadObjects()
{
	GameScreen* gameScreen = new GameScreen("GameScreen");
	this->registerObject(gameScreen);
}

void GameScene::onUnloadResources()
{
    // Unload resources specific to the game scene here
}
