#include <stddef.h>  
#include <iostream>  
#include "TextureManager.h"  

TextureManager* TextureManager::sharedInstance = nullptr;

/**
 * @brief Get the singleton instance of TextureManager
 *
 * @return TextureManager* The singleton instance
 */
TextureManager* TextureManager::getInstance()
{
	if (sharedInstance == nullptr)
	{
		sharedInstance = new TextureManager();
	}
	return sharedInstance;
}

/**
 * @brief Load all textures
 *
 * Loads a predefined set of textures into the texture map.
 */
void TextureManager::loadAll()
{
	loadTexture("eagle", "Media/Texture/Eagle.png");
	loadTexture("raptor", "Media/Texture/Raptor.png");
	loadTexture("desert_bg", "Media/Texture/Desert.png");
	loadTexture("avenger", "Media/Avenger.png");
	loadTexture("title_bg", "Media/Texture/TitleScreenBG.png");
	loadTexture("bg_box", "Media/Texture/f.png");
	loadTexture("btn_normal", "Media/Texture/b_4.png");
	loadTexture("btn_pressed", "Media/Texture/b_5.png");
	loadTexture("bar", "Media/Texture/bar_1.png");
	loadTexture("bullet", "Media/Texture/Bullet.png");

	sf::Texture* bgText;
	bgText = getTexture("desert_bg");
	bgText->setRepeated(true);
}

/**
 * @brief Load a texture from file
 *
 * @param key The key to identify the texture
 * @param path The file path to the texture
 */
void TextureManager::loadTexture(std::string key, std::string path)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	textureMap[key] = texture;
}

/**
 * @brief Get a texture by key
 *
 * @param key The key to identify the texture
 * @return sf::Texture* The texture associated with the key, or nullptr if not found
 */
sf::Texture* TextureManager::getTexture(std::string key)
{
	if (textureMap[key] != nullptr)
	{
		return textureMap[key];
	}
	else
	{
		std::cout << "Texture not found" << std::endl;
		return nullptr;
	}
}
