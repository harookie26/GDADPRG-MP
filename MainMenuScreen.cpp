#include "MainMenuScreen.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "GameObjectManager.h"

#include <iostream>
#include <string>

#include "ApplicationManager.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "UIButton.h"
#include "UIText.h"

MainMenuScreen::MainMenuScreen(std::string name) : AGameObject(name), ButtonListener()
{
}

void MainMenuScreen::initialize()
{
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("title_bg"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("MainMenuScreen");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	float posX = Game::WINDOW_WIDTH / 2;
	float posY = Game::WINDOW_HEIGHT / 2;
	this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
	this->transformable.setScale(sf::Vector2f(0.63f, 0.63f));

	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	UIButton* button1 = new UIButton("button_1", btnNormal, btnPressed);
	this->attachChild(button1);
	button1->setPosition(0, - 50);
	button1->getTransformable()->setScale(0.3f, 0.3f);
	button1->setButtonListener(this);

	UIText* button_1Text = new UIText("text_1");
	button1->attachChild(button_1Text);
	button_1Text->setPosition(0, - 20);
	button_1Text->setSize(100);
	button_1Text->setText("START");

	UIButton* button2 = new UIButton("button_2", btnNormal, btnPressed);
	this->attachChild(button2);
	button2->setPosition(0, 50);
	button2->getTransformable()->setScale(0.3f, 0.3f);
	button2->setButtonListener(this);

	UIText* button_2Text = new UIText("text_1");
	button2->attachChild(button_2Text);
	button_2Text->setPosition(0, -20);
	button_2Text->setSize(100);
	button_2Text->setText("EXIT");
}

void MainMenuScreen::onButtonClick(UIButton* button)
{
	/*std::cout << button->getName();*/

	if (button->getName() == "button_1")
	{
		GameObjectManager::getInstance()->deleteAllObjectsInScene();
		SceneManager::getInstance()->registerScene(new GameScene());
		SceneManager::getInstance()->loadScene(SceneManager::GAME_SCENE_NAME);
	}
	else if (button->getName() == "button_2")
	{
		ApplicationManager::getInstance()->applicationQuit();
	}
}

void MainMenuScreen::onButtonReleased(UIButton* button)
{
	std::cout << button->getName();
}