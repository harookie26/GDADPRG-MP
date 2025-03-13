#include "MainMenuScene.h"
#include "MainMenuScreen.h"
#include "GameObjectManager.h"

MainMenuScene::MainMenuScene()
	: AbstractScene("MainMenuScene")
{
}

void MainMenuScene::onLoadResources()
{
}

void MainMenuScene::onLoadObjects()
{
	MainMenuScreen* mainMenuScreen = new MainMenuScreen("MainMenuScreen");
	this->registerObject(mainMenuScreen);
}

void MainMenuScene::onUnloadResources()
{
}