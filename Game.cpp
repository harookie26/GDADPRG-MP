#include "Game.h"

#include <SFML/Graphics.hpp>

#include "AirplanePlayer.h"
#include "AirplaneSupport.h"
#include "ApplicationManager.h"
#include "BGObject.h"
#include "EmptyGameObject.h"
#include "EnemyAirplane.h"
#include "Renderer.h"
#include "TextureManager.h"
#include "SFXManager.h"
#include "EnemySwarmHandler.h"
#include "FontManager.h"
#include "GameScene.h"
#include "GameOverScreen.h"
#include "MainMenuScene.h"
#include "MainMenuScreen.h"
#include "QuitButton.h"
#include "ObjectPoolHolder.h"
#include "SceneManager.h"
#include "SpeedManager.h"
#include "FontManager.h"




/**
 * @brief Construct a new Game:: Game object
 *
 * Initializes the game window, player, font, and text objects.
 */
Game::Game()
	: mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Application"), mScore(0), mElapsedTime(sf::Time::Zero), mPlayer(nullptr)
{
	// Initialize ApplicationManager with the game window
	ApplicationManager::initialize(&mWindow);

	TextureManager::getInstance()->loadAll();
	FontManager::getInstance()->loadAll();

	/*BGObject* bgObject = new BGObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	AirplanePlayer* planeObject = new AirplanePlayer("PlaneOject");
	GameObjectManager::getInstance()->addObject(planeObject);

	AirplaneSupport* support1 = new AirplaneSupport("AirSupport_1", true);
	planeObject->attachChild(support1);
	support1->setPosition(50, 100);

	AirplaneSupport* support2 = new AirplaneSupport("AirSupport_2", false);
	planeObject->attachChild(support2);
	support2->setPosition(-50, 100);

	Renderer* renderer = new Renderer("PlayerSprite");
	renderer->assignDrawable(planeObject->getSprite());
	renderer->assignTargetWindow(&mWindow);*/

	/*srand(time(nullptr));
	EmptyGameObject* enemiesManager = new EmptyGameObject("EnemiesManager");
	EnemySwarmHandler* swarmHandler = new EnemySwarmHan	dler(200, "SwarmHandler", enemiesManager);
	enemiesManager->attachComponent(swarmHandler);
	GameObjectManager::getInstance()->addObject(enemiesManager);*/

	/*// Create and add the main menu screen
	MainMenuScreen* mainMenuScreen = new MainMenuScreen("MainMenuScreen");
	GameObjectManager::getInstance()->addObject(mainMenuScreen);*/
	SceneManager::getInstance()->registerScene(new MainMenuScene());
	SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);

	mWindow.setFramerateLimit(60);

}

Game::~Game()
{
	delete ApplicationManager::getInstance();
}

/**
 * @brief Main game loop
 *
 * Handles the game loop, including processing events, updating the game state, and rendering.
 */
void Game::run()
{
	sf::Clock clock;
	while (mWindow.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		processEvents();
		update(deltaTime);
		render();
		SceneManager::getInstance()->checkLoadScene();
	}
}

/**
 * @brief Process all pending events
 *
 * Handles user input events such as keyboard and mouse actions.
 */
void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			mWindow.close();
			break;
		/*case sf::Event::KeyReleased:
			break;*/
		}
		GameObjectManager::getInstance()->processInput(event);
	}
}

void Game::handleKeyPress(sf::Keyboard::Key key)
{

}

/**
 * @brief Updates the game state
 *
 * This function is called once per frame to update the game state.
 */
void Game::update(sf::Time deltaTime)
{
	SpeedManager::getInstance()->update(deltaTime.asSeconds());

	if (SceneManager::getInstance()->getActiveSceneName() != SceneManager::MAIN_MENU_SCENE_NAME)
    {
        if (!ApplicationManager::getInstance()->isPaused())
        {
            GameObjectManager::getInstance()->update(deltaTime);
			mElapsedTime += deltaTime;

			mScore = static_cast<int>(mElapsedTime.asSeconds()) * 100;
			mPlayer = dynamic_cast<AirplanePlayer*>(GameObjectManager::getInstance()->findObjectByName("PlaneObject"));
			
			if (mPlayer && mPlayer->getLives() <= 0) //  game over condition
			{

				GameObjectManager::getInstance()->deleteAllObjectsInScene();
				ApplicationManager::getInstance()->pauseApplication();
				transitionToGameOver();
				mIsGameOver = false;

			}
			
        }
		
		
		
    }
}





/**
 * @brief Transition to the game over screen
 *
 * This function is called when the game is over to display the game over screen.
 */
void Game::transitionToGameOver()
{
		mIsGameOver = true;

		// Create and add the game over screen
		GameOverScreen* gameOverScreen = new GameOverScreen("gameOverScreen");
		gameOverScreen->initialize();
		gameOverScreen->setScore(mScore);
		mElapsedTime = sf::Time::Zero; // Reset elapsed time for the next game
		mScore = 0; // Reset score for the next game
		GameObjectManager::getInstance()->addObject(gameOverScreen);
	
}





/**
 * @brief Render the game objects
 *
 * Clears the window and draws the player and text objects.
 */
void Game::render()
{
	mWindow.clear();
	GameObjectManager::getInstance()->draw(&mWindow);
	

	if (!mIsGameOver && SceneManager::getInstance()->getActiveSceneName() != SceneManager::MAIN_MENU_SCENE_NAME)
	{
		const sf::Font* font = FontManager::getInstance()->getFont("default");
		sf::Text scoreText; 
		scoreText.setFont(*font);
		scoreText.setString("Score: " + std::to_string(mScore));
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(500, 10);
		mWindow.draw(scoreText);
	}
	mWindow.display();


}
