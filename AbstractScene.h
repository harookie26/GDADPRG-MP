#pragma once

#include "AGameObject.h"

class AbstractScene
{
public:
	AbstractScene(std::string sceneName);

	virtual void onLoadResources() = 0;
	virtual void onLoadObjects() = 0;

	virtual void onUnloadResources() = 0;
	virtual void onUnloadObjects();

	std::string getSceneName();

protected:
	void registerObject(AGameObject* object);
	std::string sceneName;
};