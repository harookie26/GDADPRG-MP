#pragma once
#include "AGameObject.h"
#include "ButtonListener.h"
#include <string>

class QuitButton : public AGameObject, public ButtonListener
{
public:
    QuitButton(std::string name);

    void initialize();

    void onButtonClick(UIButton* button);
    void onButtonReleased(UIButton* button);
};
