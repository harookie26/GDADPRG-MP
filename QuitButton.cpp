#include "QuitButton.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "ApplicationManager.h"
#include "ConfirmExitScreen.h"
#include "UIButton.h"
#include "UIText.h"

QuitButton::QuitButton(std::string name) : AGameObject(name), ButtonListener()
{
}

void QuitButton::initialize()
{
    sf::Sprite* sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("bar"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
    sprite->setScale(0.6f, 0.6f);

    sprite->setPosition(Game::WINDOW_WIDTH - textureSize.x / 2.5, Game::WINDOW_HEIGHT - textureSize.y + 25);

    Renderer* renderer = new Renderer("QuitBar");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);

    sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
    sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

    UIButton* quitButton = new UIButton("quitButton", btnNormal, btnPressed);
    this->attachChild(quitButton);
	quitButton->setPosition(Game::WINDOW_WIDTH - 85, Game::WINDOW_HEIGHT - 43);
    quitButton->getTransformable()->setScale(0.105f, 0.105f);
    quitButton->setButtonListener(this);

    UIText* quitButtonText = new UIText("quitButtonText");
    quitButton->attachChild(quitButtonText);
    quitButtonText->setPosition(0, -20);
    quitButtonText->setSize(100);
    quitButtonText->setText("QUIT");
}

void QuitButton::onButtonClick(UIButton* button)
{
    if (button->getName() == "quitButton")
    {
        ApplicationManager::getInstance()->pauseApplication();
        GameObjectManager::getInstance()->addObject(new ConfirmExitScreen("confirmExitScreen"));
    }
}

void QuitButton::onButtonReleased(UIButton* button)
{
}
