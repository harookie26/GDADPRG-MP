#include "EnemySwarmHandler.h"
#include "EnemyAirplane.h"
#include "ObjectPoolHolder.h"
#include "GameObjectPool.h"
#include "EnemyTorpedo.h"
#include "Game.h"

#include <iostream>

/**
 * @brief Construct a new EnemySwarmHandler object
 *
 * @param numEnemies The number of enemies to initialize in the pool
 * @param name The name of the component
 * @param parent The parent game object
 */
EnemySwarmHandler::EnemySwarmHandler(int numEnemies, std::string name, AGameObject* parent)
    : AbstractComponent(name, Script)
{
    this->enemyPool = new GameObjectPool(ObjectPoolHolder::ENEMY_POOL_TAG, new EnemyAirplane("enemy"), numEnemies, parent);
    this->enemyTorpedoPool = new GameObjectPool(ObjectPoolHolder::PROJECTILE_POOL_TAG, new EnemyTorpedo("enemy_torpedo"), numEnemies, parent);
    enemyPool->initialize();
    enemyTorpedoPool->initialize();
    ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
    ObjectPoolHolder::getInstance()->registerObjectPool(enemyTorpedoPool);
}

/**
 * @brief Destroy the EnemySwarmHandler object
 *
 */
EnemySwarmHandler::~EnemySwarmHandler()
{
    delete this->enemyPool;
    delete this->enemyTorpedoPool;
}

/**
 * @brief Perform the enemy spawning logic
 *
 */
void EnemySwarmHandler::perform()
{
    this->ticks += this->deltaTime.asSeconds();
    this->elapsedTime += this->deltaTime.asSeconds();

    // Update the spawn interval based on elapsed time
    updateSpawnInterval(this->deltaTime.asSeconds());

    if (this->ticks >= this->SPAWN_INTERVAL)
    {
        this->ticks = 0.0f;

        // Randomly choose which type of enemy to spawn with a bias towards EnemyAirplane
        int randomChoice = rand() % 10; // Generate a number between 0 and 9
        AbstractPoolable* enemy = nullptr;

        if (randomChoice < 8 && this->enemyPool->hasObjectAvailable(1)) // 80% chance to spawn EnemyAirplane
        {
            enemy = this->enemyPool->requestPoolableBatch(1)[0];
        }
        else if (randomChoice >= 8 && this->enemyTorpedoPool->hasObjectAvailable(1)) // 20% chance to spawn EnemyTorpedo
        {
            enemy = this->enemyTorpedoPool->requestPoolableBatch(1)[0];
        }

        if (enemy != nullptr)
        {
            enemy->onActivate();
            enemy->setEnabled(true);
        }
    }
}

/**
 * @brief Update the spawn interval based on elapsed game time
 *
 * @param deltaTime The time elapsed since the last update
 */
void EnemySwarmHandler::updateSpawnInterval(float deltaTime)
{
    // Decrease the spawn interval over time, but not below the minimum spawn interval
    if (SPAWN_INTERVAL > MIN_SPAWN_INTERVAL)
    {
        SPAWN_INTERVAL -= deltaTime * 0.01f; // Adjust the decrement rate as needed
        if (SPAWN_INTERVAL < MIN_SPAWN_INTERVAL)
        {
            SPAWN_INTERVAL = MIN_SPAWN_INTERVAL;
        }
    }
}
