#include "GameOverScreen.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "ApplicationManager.h"
#include "PauseWindow.h"
#include "SceneManager.h"
#include "UIButton.h"
#include "UIText.h"

GameOverScreen::GameOverScreen(std::string name) : AGameObject(name), ButtonListener()
{
}

void GameOverScreen::initialize()
{
    sf::Sprite* sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("pause_window"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
    sprite->setScale(0.75f, 0.75f); // Adjust the scale factors as needed

    Renderer* renderer = new Renderer("GameOverScreen");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);

    float posX = Game::WINDOW_WIDTH / 2;
    float posY = Game::WINDOW_HEIGHT / 2;
    this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2 - 30);
    this->transformable.setScale(sf::Vector2f(0.7f, 0.7f));

    sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
    sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

    UIText* gameOverText = new UIText("gameOverText");
    this->attachChild(gameOverText);
    gameOverText->setText("Game Over");
    //scoreText->setText("Score: " + std::to_string(mScore));
    
    sf::FloatRect textBounds = gameOverText->text->getLocalBounds();
    sf::FloatRect spriteBounds = sprite->getGlobalBounds();

    float scale = std::min((spriteBounds.width * 0.8f) / textBounds.width, (spriteBounds.height * 0.2f) / textBounds.height);
    gameOverText->text->setScale(scale, scale);
    gameOverText->setPosition(0, -80);


    UIText* scoreText = new UIText("scoreText");
    this->attachChild(scoreText);
    scoreText->setText("Score: ");
    scoreText->text->setScale(scale/2.5, scale/2.5);
    scoreText->setPosition(-100, 0);
    
    std::string score = std::to_string(mScore);

    UIText* pointsText = new UIText("pointsText");
    this->attachChild(pointsText);
    pointsText->setText(score);
    pointsText->text->setScale(scale / 2.5, scale / 2.5);
    pointsText->setPosition(100, 0);


    UIButton* yesButton = new UIButton("endButton", btnNormal, btnPressed);
    this->attachChild(yesButton);
    yesButton->setPosition(0, 140);
    yesButton->getTransformable()->setScale(3.0f, 1.7f);
    yesButton->setButtonListener(this);

    UIText* yesButtonText = new UIText("endText");
    yesButton->attachChild(yesButtonText);
    yesButtonText->setPosition(2, -5);
    yesButtonText->setSize(15);
	yesButtonText->getTransformable()->setScale(0.8f, 1.7f);
    yesButtonText->setText("Main Menu");


}

void GameOverScreen::setScore(int score)
{
    mScore = score;
}

void GameOverScreen::onButtonClick(UIButton* button)
{
    std::string buttonName = button->getName();

    if (buttonName == "endButton")
    {
        GameObjectManager::getInstance()->deleteAllObjectsInScene();
        SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
        
		
    }
   /* else if (buttonName == "noButton")
    {
        GameObjectManager::getInstance()->deleteObject(this);
        GameObjectManager::getInstance()->addObject(new PauseWindow("PauseWindow"));
    }*/
}

void GameOverScreen::onButtonReleased(UIButton* button)
{
    // No action needed on button release
}