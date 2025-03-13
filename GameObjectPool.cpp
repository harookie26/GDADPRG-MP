#include "GameObjectPool.h"
#include "GameObjectManager.h"
#include <iostream>

/**
 * @brief Construct a new GameObjectPool object
 *
 * @param tag The tag associated with the pool
 * @param poolableCopy A copy of the poolable object to be used for cloning
 * @param poolableSize The maximum size of the pool
 * @param parent The parent game object, if any
 */
GameObjectPool::GameObjectPool(std::string tag, AbstractPoolable* poolableCopy, int poolableSize, AGameObject* parent)
{
    this->tag = tag;
    this->objectCopy = poolableCopy;
    this->maxPoolSize = poolableSize;
    this->parent = parent;
}

/**
 * @brief Destroy the GameObjectPool object
 *
 */
GameObjectPool::~GameObjectPool()
{
    delete this->objectCopy;
    this->objectCopy = nullptr;
    this->parent = nullptr;
}

/**
 * @brief Initialize the pool by creating the poolable objects and adding them to the available list
 *
 */
void GameObjectPool::initialize()
{
    for (int i = 0; i < this->maxPoolSize; i++)
    {
        AbstractPoolable* poolableObject = this->objectCopy->clone();

        if (this->parent != nullptr)
        {
            this->parent->attachChild(poolableObject);
        }
        else
        {
            GameObjectManager::getInstance()->addObject(poolableObject);
        }

        poolableObject->setEnabled(false);
        this->availableObjects.push_back(poolableObject);
    }
}

/**
 * @brief Check if there are enough objects available in the pool
 *
 * @param requestSize The number of objects requested
 * @return true If there are enough objects available
 * @return false If there are not enough objects available
 */
bool GameObjectPool::hasObjectAvailable(int requestSize)
{
    return requestSize <= this->availableObjects.size();
}

/**
 * @brief Request a single poolable object from the pool
 *
 * @return AbstractPoolable* The requested poolable object, or nullptr if none are available
 */
AbstractPoolable* GameObjectPool::requestPoolable()
{
    if (this->hasObjectAvailable(1))
    {
        AbstractPoolable* poolableObject = this->availableObjects[this->availableObjects.size() - 1];
        this->availableObjects.erase(this->availableObjects.begin() + this->availableObjects.size() - 1);
        this->usedObjects.push_back(poolableObject);

        this->setEnabled(poolableObject, true);
        return poolableObject;
    }
    else
    {
        std::cout << "No more poolable " << this->objectCopy->getName() << " available!" << std::endl;
        return nullptr;
    }
}

/**
 * @brief Request a batch of poolable objects from the pool
 *
 * @param size The number of objects requested
 * @return std::vector<AbstractPoolable*> A vector containing the requested poolable objects
 */
std::vector<AbstractPoolable*> GameObjectPool::requestPoolableBatch(int size)
{
    std::vector<AbstractPoolable*> returnList;

    if (this->hasObjectAvailable(size))
    {
        for (int i = 0; i < size; i++)
        {
            returnList.push_back(this->requestPoolable());
        }
    }
    else
    {
        std::cout << "Insufficient " << this->objectCopy->getName() << " available in pool. " << "Count is: " << this->availableObjects.size() << " while request is " << size << std::endl;
    }
    return returnList;
}

/**
 * @brief Get the tag associated with the pool
 *
 * @return std::string The tag
 */
std::string GameObjectPool::getTag()
{
    return this->tag;
}

/**
 * @brief Set the enabled state of a poolable object
 *
 * @param poolableObject The poolable object
 * @param flag The enabled state to set
 */
void GameObjectPool::setEnabled(AbstractPoolable* poolableObject, bool flag)
{
    if (flag)
    {
        poolableObject->setEnabled(true);
        poolableObject->onActivate();
    }
    else
    {
        poolableObject->setEnabled(false);
        poolableObject->onRelease();
    }
}

/**
 * @brief Release a poolable object back to the pool
 *
 * @param poolableObject The poolable object to release
 */
void GameObjectPool::releasePoolable(AbstractPoolable* poolableObject)
{
    auto it = std::find(this->usedObjects.begin(), this->usedObjects.end(), poolableObject);
    if (it != this->usedObjects.end())
    {
        this->usedObjects.erase(it);
        this->availableObjects.push_back(poolableObject);
        this->setEnabled(poolableObject, false);
    }
}

/**
 * @brief Release a batch of poolable objects back to the pool
 *
 * @param objectList A vector containing the poolable objects to release
 */
void GameObjectPool::releasePoolableBatch(std::vector<AbstractPoolable*> objectList)
{
    for (AbstractPoolable* poolableObject : objectList)
    {
        this->releasePoolable(poolableObject);
    }
}