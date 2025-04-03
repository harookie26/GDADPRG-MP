#include "ConfirmExitScreen.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "ApplicationManager.h"
#include "PauseWindow.h"
#include "SceneManager.h"
#include "UIButton.h"
#include "UIText.h"

ConfirmExitScreen::ConfirmExitScreen(std::string name) : AGameObject(name), ButtonListener()
{
}

void ConfirmExitScreen::initialize()
{
    sf::Sprite* sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("bg_box"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
    sprite->setScale(0.75f, 0.75f); // Adjust the scale factors as needed

    Renderer* renderer = new Renderer("ConfirmExitScreen");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);

    float posX = Game::WINDOW_WIDTH / 2;
    float posY = Game::WINDOW_HEIGHT / 2;
    this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2 - 30);
    this->transformable.setScale(sf::Vector2f(0.7f, 0.7f));

    sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
    sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

    UIText* confirmationText = new UIText("confirmExitText");
    this->attachChild(confirmationText);
    confirmationText->setText("Are you sure you want to quit the game?");

    sf::FloatRect textBounds = confirmationText->text->getLocalBounds();
    sf::FloatRect spriteBounds = sprite->getGlobalBounds();

    float scale = std::min((spriteBounds.width * 0.8f) / textBounds.width, (spriteBounds.height * 0.2f) / textBounds.height);
    confirmationText->text->setScale(scale, scale);
    confirmationText->setPosition(0, -50);

    UIButton* yesButton = new UIButton("yesButton", btnNormal, btnPressed);
    this->attachChild(yesButton);
    yesButton->setPosition(-100, 100);
    yesButton->getTransformable()->setScale(0.3f, 0.3f);
    yesButton->setButtonListener(this);

    UIText* yesButtonText = new UIText("yesText");
    yesButton->attachChild(yesButtonText);
    yesButtonText->setPosition(0, -20);
    yesButtonText->setSize(100);
    yesButtonText->setText("YES");

    UIButton* noButton = new UIButton("noButton", btnNormal, btnPressed);
    this->attachChild(noButton);
    noButton->setPosition(100, 100);
    noButton->getTransformable()->setScale(0.3f, 0.3f);
    noButton->setButtonListener(this);

    UIText* noButtonText = new UIText("noText");
    noButton->attachChild(noButtonText);
    noButtonText->setPosition(0, -20);
    noButtonText->setSize(100);
    noButtonText->setText("NO");
}

void ConfirmExitScreen::onButtonClick(UIButton* button)
{
    std::string buttonName = button->getName();

    if (buttonName == "yesButton")
    {
        GameObjectManager::getInstance()->deleteAllObjectsInScene();
        SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
    }
    else if (buttonName == "noButton")
    {
        GameObjectManager::getInstance()->deleteObject(this);
        GameObjectManager::getInstance()->addObject(new PauseWindow("PauseWindow"));
    }
}

void ConfirmExitScreen::onButtonReleased(UIButton* button)
{
    // No action needed on button release
}
