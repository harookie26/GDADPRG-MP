#include "PauseWindow.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "ApplicationManager.h"
#include "ConfirmExitScreen.h"
#include "SceneManager.h"
#include "UIButton.h"
#include "UIText.h"

PauseWindow::PauseWindow(std::string name) : AGameObject(name), ButtonListener()
{
}

void PauseWindow::initialize()
{
    sf::Sprite* sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("pause_window"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
    sprite->setScale(0.75f, 0.75f); // Adjust the scale factors as needed

    Renderer* renderer = new Renderer("PauseWindow");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);

    float posX = Game::WINDOW_WIDTH / 2;
    float posY = Game::WINDOW_HEIGHT / 2;
    this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2 - 30);
    this->transformable.setScale(sf::Vector2f(0.7f, 0.7f));

    sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
    sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

    UIText* confirmationText = new UIText("PauseText");
    this->attachChild(confirmationText);
    confirmationText->setText("PAUSED");

    sf::FloatRect textBounds = confirmationText->text->getLocalBounds();
    sf::FloatRect spriteBounds = sprite->getGlobalBounds();

    float scale = std::min((spriteBounds.width * 0.8f) / textBounds.width, (spriteBounds.height * 0.2f) / textBounds.height);
    confirmationText->text->setScale(scale, scale);
    confirmationText->setPosition(0, -50);

    UIButton* yesButton = new UIButton("resumeButton", btnNormal, btnPressed);
    this->attachChild(yesButton);
    yesButton->setPosition(-100, 140);
    yesButton->getTransformable()->setScale(1.5f, 1.5f);
    yesButton->setButtonListener(this);

    UIText* yesButtonText = new UIText("resumeText");
    yesButton->attachChild(yesButtonText);
    yesButtonText->setPosition(5, -5);
    yesButtonText->setSize(15);
    yesButtonText->setText("Resume");

    UIButton* noButton = new UIButton("quitButton", btnNormal, btnPressed);
    this->attachChild(noButton);
    noButton->setPosition(100, 140);
    noButton->getTransformable()->setScale(1.5f, 1.5f);
    noButton->setButtonListener(this);

    UIText* noButtonText = new UIText("quitText");
    noButton->attachChild(noButtonText);
    noButtonText->setPosition(0, -5);
    noButtonText->setSize(25);
    noButtonText->setText("Quit");
}

void PauseWindow::onButtonClick(UIButton* button)
{
    std::string buttonName = button->getName();

    if (buttonName == "resumeButton")
    {
        ApplicationManager::getInstance()->resumeApplication();
        GameObjectManager::getInstance()->deleteObject(this);
    }

    if (buttonName == "quitButton")
    {
        GameObjectManager::getInstance()->deleteObject(this);
        GameObjectManager::getInstance()->addObject(new ConfirmExitScreen("confirmExitScreen"));
    }
}



void PauseWindow::onButtonReleased(UIButton* button)
{
    // No action needed on button release
}
