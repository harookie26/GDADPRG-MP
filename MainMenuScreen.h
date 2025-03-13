#pragma once
#include "AGameOBject.h"
#include "ButtonListener.h"
#include <string>

class MainMenuScreen : public AGameObject, public ButtonListener
{
public:
	MainMenuScreen(std::string name);

	void initialize();

	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);
};