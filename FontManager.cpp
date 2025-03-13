#include "FontManager.h"
#include <iostream>

FontManager* FontManager::sharedInstance = NULL;

FontManager* FontManager::getInstance()
{
	if (sharedInstance == NULL)
	{
		sharedInstance = new FontManager();
	}
	return sharedInstance;
}

void FontManager::loadAll()
{
	loadFont("default", "Media/Sansation.ttf");
}

void FontManager::loadFont(std::string key, std::string path)
{
	sf::Font* font = new sf::Font();
	font->loadFromFile(path);
	fontMap[key] = font;
}

sf::Font* FontManager::getFont(std::string key)
{
	if (fontMap[key] != NULL)
	{
		return fontMap[key];
	}
	else
	{
		std::cout << "No font found for " << key << std::endl;
		return NULL;
	}
}