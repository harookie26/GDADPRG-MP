#include "SpeedManager.h"
#include"iostream"
SpeedManager* SpeedManager::instance = nullptr;

SpeedManager::SpeedManager() : speedMultiplier(1.0f), incrementRate(0.01f) {}

SpeedManager* SpeedManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new SpeedManager();
    }
    return instance;
}

void SpeedManager::update(float deltaTime)
{
    speedMultiplier += incrementRate * deltaTime;
	
}


float SpeedManager::getSpeedMultiplier() const
{
    return speedMultiplier;
}

void SpeedManager::resetSpeed()
{
	speedMultiplier = 1.0f;
}