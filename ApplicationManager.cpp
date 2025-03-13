#include "ApplicationManager.h"

ApplicationManager* ApplicationManager::sharedInstance = nullptr;

void ApplicationManager::initialize(sf::RenderWindow* window)
{
    if (sharedInstance == nullptr)
    {
        sharedInstance = new ApplicationManager();
        sharedInstance->window = window;
        sharedInstance->state = Running;
    }
}

ApplicationManager* ApplicationManager::getInstance()
{
    return sharedInstance;
}

void ApplicationManager::applicationQuit()
{
    window->close();
}

void ApplicationManager::pauseApplication()
{
    state = Paused;
}

void ApplicationManager::resumeApplication()
{
    state = Running;
}

bool ApplicationManager::isPaused()
{
    return state == Paused;
}

ApplicationManager::ApplicationManager()
{
}

ApplicationManager::~ApplicationManager()
{
}

void ApplicationManager::setState(GameState newState)
{
    state = newState;
}