#pragma once

#include "GenericInputController.h"
#include "UIButton.h"
#include "ButtonListener.h"

class UIButtonInputController : public GenericInputController
{
public:
	UIButtonInputController(std::string name, ButtonListener* listener);
	~UIButtonInputController();

	void perform();

private:
	ButtonListener* buttonListener;
	bool pressed = false;
};