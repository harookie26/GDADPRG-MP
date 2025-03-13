#include "ObjectPoolHolder.h"

/**
 * @brief Tag for the enemy pool
 *
 */
const std::string ObjectPoolHolder::ENEMY_POOL_TAG = "EnemyPool";

/**
 * @brief Tag for the projectile pool
 *
 */
const std::string ObjectPoolHolder::PROJECTILE_POOL_TAG = "ProjectilePool";

/**
 * @brief Singleton instance of ObjectPoolHolder
 *
 */
ObjectPoolHolder* ObjectPoolHolder::sharedInstance = nullptr;

/**
 * @brief Get the singleton instance of ObjectPoolHolder
 *
 * @return ObjectPoolHolder* Pointer to the singleton instance
 */
ObjectPoolHolder* ObjectPoolHolder::getInstance()
{
    if (sharedInstance == nullptr)
    {
        sharedInstance = new ObjectPoolHolder();
    }
    return sharedInstance;
}

/**
 * @brief Register a game object pool
 *
 * @param pool Pointer to the game object pool to register
 */
void ObjectPoolHolder::registerObjectPool(GameObjectPool* pool)
{
    this->poolMap[pool->getTag()] = pool;
}

/**
 * @brief Unregister a game object pool
 *
 * @param pool Pointer to the game object pool to unregister
 */
void ObjectPoolHolder::unregisterObjectPool(GameObjectPool* pool)
{
    this->poolMap.erase(pool->getTag());
    delete pool;
}

/**
 * @brief Get a game object pool by its tag
 *
 * @param tag The tag of the game object pool
 * @return GameObjectPool* Pointer to the game object pool
 */
GameObjectPool* ObjectPoolHolder::getPool(std::string tag)
{
    return this->poolMap[tag];
}