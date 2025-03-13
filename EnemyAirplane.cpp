#include "EnemyAirplane.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "EnemyBehaviour.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "PhysicsManager.h"

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

    this->setPosition(Game::WINDOW_WIDTH / 2, -30);
    this->getTransformable()->move(rand() % SPAWN_RANGE - rand() % SPAWN_RANGE, 0);
    this->getTransformable()->setRotation(180);

    Renderer* renderer = new Renderer("EnemySprite");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);

    EnemyBehaviour* behaviour = new EnemyBehaviour("EnemyBehaviour");
    this->attachComponent(behaviour);
    behaviour->configure(1.0f);

	this->collider = new Collider("EnemyCollider");
    this->collider->setLocalBounds(sprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);
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

	//PhysicsManager::getInstance()->trackObject(this->collider);

    this->setPosition(Game::WINDOW_WIDTH / 2, -30);
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
		std::cout << "Collided with: " << gameObject->getName() << std::endl;
		GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
        enemyPool->releasePoolable((AbstractPoolable*)this);
	}
}

void EnemyAirplane::onCollisionExit(AGameObject* gameObject)
{
}