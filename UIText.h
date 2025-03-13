#pragma once
#include "AGameObject.h"
#include <string>

class UIText : public AGameObject
{
public:
	UIText(std::string name);
	~UIText();
	void initialize();
	void setText(std::string text);
	std::string getText();
	void setSize(unsigned int size);

	sf::Text* text;

private:
	
};