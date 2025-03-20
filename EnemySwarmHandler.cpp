#include "EnemySwarmHandler.h"
#include "EnemyAirplane.h"
#include "ObjectPoolHolder.h"
#include "GameObjectPool.h"

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
    enemyPool->initialize();
    ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
}

/**
 * @brief Destroy the EnemySwarmHandler object
 *
 */
EnemySwarmHandler::~EnemySwarmHandler()
{
    delete this->enemyPool;
}

/**
 * @brief Perform the enemy spawning logic
 *
 */
void EnemySwarmHandler::perform()
{
    GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
    this->ticks += this->deltaTime.asSeconds();

    if (this->ticks > SPAWN_INTERVAL)
    {
        this->ticks = 0.0f;
        enemyPool->requestPoolable();
    }
	if (SPAWN_INTERVAL > 1) {
		SPAWN_INTERVAL -= 0.000005;
        //std::cout << SPAWN_INTERVAL << std::endl;
	}
	
}