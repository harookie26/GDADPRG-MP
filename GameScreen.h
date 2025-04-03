#pragma once
#include "AGameObject.h"
#include "ButtonListener.h"
#include <string>

class GameScreen : public AGameObject, public ButtonListener
{
public:
	GameScreen(std::string name);

	void initialize();

	void processInput(sf::Event event) override;

	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);

	void registerObject(AGameObject* object); // Add this method declaration
};