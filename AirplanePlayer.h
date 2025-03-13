#pragma once
#include "AGameObject.h"
#include "TextureManager.h"
#include "Game.h"

#include <iostream>

class AirplanePlayer : public AGameObject
{
public:
	AirplanePlayer(std::string name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	sf::Transformable* getTransformable();
	sf::Drawable* getSprite();

private:
	const float SPEED_MULTIIPLIER = 100.0f;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
};
