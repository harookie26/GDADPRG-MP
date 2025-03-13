#pragma once
#include "AbstractScene.h"

class MainMenuScene : public AbstractScene
{
public:
	MainMenuScene();

	void onLoadResources();
	void onLoadObjects();

	void onUnloadResources();
};