#pragma once
#include "AGameObject.h"
#include "ButtonListener.h"
#include <string>

class ConfirmExitScreen : public AGameObject, public ButtonListener
{
public:
    ConfirmExitScreen(std::string name);

    void initialize();

    void onButtonClick(UIButton* button);
    void onButtonReleased(UIButton* button);

    sf::FloatRect getGlobalBounds() const;
    sf::FloatRect getLocalBounds() const;

private:
    sf::Sprite* sprite;
};

