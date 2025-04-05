#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Entity.h"
#include "GameObjectManager.h"
#include "AirplanePlayer.h"
class AirplanePlayer;
class Game
{
public:
	Game();
	~Game();
	void run();
	
	

	const static int WINDOW_WIDTH = 640;
	const static int WINDOW_HEIGHT = 480;

private:
	
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void handleKeyPress(sf::Keyboard::Key key);
	void transitionToGameOver();


	sf::RenderWindow mWindow;
	int mScore; //   keep track of the score
	sf::Time mElapsedTime; //  elapsed time for scoring
	AirplanePlayer* mPlayer;
	bool mIsGameOver = false;
protected:
	
};

