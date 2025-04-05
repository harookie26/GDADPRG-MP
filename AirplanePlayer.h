#pragma once
#include "AGameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Collider.h"
#include "CollisionListener.h"

#include <iostream>
#include <vector>

class AirplanePlayer : public AGameObject, public CollisionListener
{
public:
    AirplanePlayer(std::string name);
    void initialize();
    void processInput(sf::Event event);
    void update(sf::Time deltaTime);
    sf::Transformable* getTransformable();
    sf::Drawable* getSprite();

    void takeDamage(); // Method to reduce lives
    void onCollisionEnter(AGameObject* gameObject) override;
    void onCollisionExit(AGameObject* gameObject) override;
    int getLives();

    std::vector<sf::Sprite*> heartSprites; // Heart sprites
    Collider* collider;

private:
    const float SPEED_MULTIIPLIER = 100.0f;
    bool moveUp = false;
    bool moveDown = false;
    bool moveLeft = false;
    bool moveRight = false;

    int lives = 3; // Number of lives
    
};
