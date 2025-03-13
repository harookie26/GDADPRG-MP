#pragma once
#include "AGameObject.h"
#include "UIButtonInputController.h"
#include "ButtonListener.h"

class UIButton : public AGameObject
{
public:
	UIButton(std::string name, sf::Texture* normalTexture, sf::Texture* pressedTexture);
	void initialize();

	void changeButtonToNormal();
	void changeButtonToPressed();
	sf::FloatRect getGlobalBounds();
	sf::FloatRect getLocalBounds();
	void setButtonListener(ButtonListener* listener);

private:
	sf::Texture* normalTexture;
	sf::Texture* pressedTexture;
	sf::Sprite* sprite;
	ButtonListener* listener;
};