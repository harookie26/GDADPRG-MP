#pragma once

#include "AbstractComponent.h"
#include "GameObjectPool.h"

class PlayerMovement : public AbstractComponent
{
public:
	PlayerMovement(std::string name);
	void perform() override;

private:
	GameObjectPool* projectilePool;
	const float SPEED_MULTIPLIER = 300.0f;
	const float BULLET_SPAWN_INTERVAL = 1.5f;
	float ticks = 0.0f;
};
