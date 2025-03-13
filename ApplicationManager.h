#pragma once

#include <SFML/Graphics.hpp>

class ApplicationManager
{
public:
	static void initialize(sf::RenderWindow* window);
	static ApplicationManager* getInstance();
	void applicationQuit();
	void pauseApplication();
	void resumeApplication();
	bool isPaused();

	~ApplicationManager();

	enum GameState { Running = 0, Paused = 1};
	void setState(GameState newState);


private:
	ApplicationManager();
	ApplicationManager(ApplicationManager const&) {};
	ApplicationManager& operator=(ApplicationManager const&) {};
	
	static ApplicationManager* sharedInstance;
	sf::RenderWindow* window;
	GameState state;
};