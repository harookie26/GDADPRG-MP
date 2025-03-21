#pragma once
#include "AbstractComponent.h"
#include "GameObjectPool.h"

class EnemySwarmHandler : public AbstractComponent
{
public:
    EnemySwarmHandler(int numEnemies, std::string name, AGameObject* parent);
    ~EnemySwarmHandler();
    void perform() override;

private:
	GameObjectPool* enemyPool;
	const float SPAWN_INTERVAL = 2.0f;
	float ticks = 0.0f;
};
    void updateSpawnInterval(float deltaTime);

    GameObjectPool* enemyPool;
    GameObjectPool* enemyTorpedoPool;
    float SPAWN_INTERVAL = 2.0f;
    float MIN_SPAWN_INTERVAL = 1.0f; // Minimum spawn interval
    float ticks = 0.0f;
    float elapsedTime = 0.0f; // Track elapsed game time
};
