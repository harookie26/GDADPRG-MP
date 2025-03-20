#pragma once
#include "AbstractComponent.h"
#include "GameObjectPool.h"

class EnemySwarmHandler : public AbstractComponent
{
public:
	EnemySwarmHandler(int numEnemies, std::string name, AGameObject* parent);
	~EnemySwarmHandler();
	void perform();

private:
	GameObjectPool* enemyPool;
	float SPAWN_INTERVAL = 2.0f;
	float ticks = 0.0f;
};