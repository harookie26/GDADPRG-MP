#include "EnemyAirplane.h"

#include "AirplanePlayer.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "EnemyBehaviour.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "PhysicsManager.h"
#include "SFXManager.h"
/**
 * @brief Construct a new EnemyAirplane object
 *
 * @param name The name of the enemy airplane
 */
EnemyAirplane::EnemyAirplane(std::string name)
	: AbstractPoolable(name), CollisionListener(), collider(nullptr)
{
}

/**
 * @brief Destroy the EnemyAirplane object
 *
 */
EnemyAirplane::~EnemyAirplane()
{
    delete this->sprite;
}

/**
 * @brief Initialize the enemy airplane
 *
 */
void EnemyAirplane::initialize()
{
    this->sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("avenger"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
    this->sprite->setScale(2.0f, 2.0f); // Scale the sprite by 2x
    this->setPosition(Game::WINDOW_WIDTH / 2, -30);
    this->getTransformable()->move(rand() % SPAWN_RANGE - rand() % SPAWN_RANGE, 0);
    this->getTransformable()->setRotation(180);

    Renderer* renderer = new Renderer("EnemySprite");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);

    EnemyBehaviour* behaviour = new EnemyBehaviour("EnemyBehaviour");
    behaviour->setSpeedMultiplier(1.0f);
    this->attachComponent(behaviour);
    behaviour->configure(1.0f);

    this->collider = new Collider("EnemyCollider");

    // Retrieve the global bounds of the sprite
    sf::FloatRect globalBounds = sprite->getGlobalBounds();

    // Scale the bounds to be slightly smaller
    float scaleFactor = 0.3f; // Adjust this value as needed
    sf::FloatRect scaledBounds(
        globalBounds.left + (globalBounds.width * (1 - scaleFactor) / 2),
        globalBounds.top + (globalBounds.height * (1 - scaleFactor) / 2),
        globalBounds.width * (scaleFactor + 0.2f),
        globalBounds.height * scaleFactor
    );

    // Set the scaled bounds to the collider
    this->collider->setLocalBounds(scaledBounds);
    this->collider->setCollisionListener(this);
    this->attachComponent(this->collider);

	SFXManager::getInstance()->loadAll();
}


/**
 * @brief Actions to perform when the enemy airplane is released
 *
 */
void EnemyAirplane::onRelease()
{
	PhysicsManager::getInstance()->untrackObject(this->collider);
}

/**
 * @brief Actions to perform when the enemy airplane is activated
 *
 */
void EnemyAirplane::onActivate()
{
	EnemyBehaviour* behaviour = (EnemyBehaviour*)this->findComponentByName("EnemyBehaviour");
    behaviour->reset();

	PhysicsManager::getInstance()->trackObject(this->collider);

    this->setPosition(Game::WINDOW_WIDTH / 2, 0);
	this->getTransformable()->move(rand() % SPAWN_RANGE - rand() % SPAWN_RANGE, 0);
}

/**
 * @brief Clone the enemy airplane
 *
 * @return AbstractPoolable* Pointer to the cloned enemy airplane
 */
AbstractPoolable* EnemyAirplane::clone()
{
    AbstractPoolable* copyObj = new EnemyAirplane(this->name);
    return copyObj;
}

void EnemyAirplane::onCollisionEnter(AGameObject* gameObject)
{
	if (gameObject->getName().find("projectile") != std::string::npos)
	{
        SFXManager::getInstance()->playSound("explosion");
		//std::cout << "EnemyPlane collided with: " << gameObject->getName() << std::endl;
		GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
        enemyPool->releasePoolable((AbstractPoolable*)this);
	}

	if (gameObject->getName().find("PlaneObject") != std::string::npos)
	{
        SFXManager::getInstance()->playSound("explosion");
		std::cout << "Enemy hit player" << std::endl;
        GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
        enemyPool->releasePoolable((AbstractPoolable*)this);
	}
}

void EnemyAirplane::onCollisionExit(AGameObject* gameObject)
{
}