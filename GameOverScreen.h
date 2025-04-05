#pragma once

#include "AGameObject.h"
#include "ButtonListener.h"



class GameOverScreen : public AGameObject, public ButtonListener
{
private:  
	int mScore; // Variable to store the score
   
public:
    GameOverScreen(std::string name);
    void initialize() override;
    void onButtonClick(UIButton* button) override;
    void onButtonReleased(UIButton* button) override;
	void setScore(int score);
};