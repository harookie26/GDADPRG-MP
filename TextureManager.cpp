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
	loadTexture("eagle", "Media/Textures/main.png");
	loadTexture("raptor", "Media/Textures/scout.png");
	loadTexture("desert_bg", "Media/Textures/bg1.png");
	loadTexture("avenger", "Media/Textures/scout.png");
	loadTexture("enemy_torpedo", "Media/Textures/torpedo.png");
	loadTexture("title_bg", "Media/Texture/TitleScreenBG.png");
	loadTexture("bg_box", "Media/Texture/f.png");
	loadTexture("btn_normal", "Media/Texture/b_4.png");
	loadTexture("btn_pressed", "Media/Texture/b_5.png");
	loadTexture("bar", "Media/Texture/bar_1.png");
	loadTexture("bullet", "Media/Texture/Bullet.png");

	sf::Texture* bgText;
	bgText = getTexture("desert_bg");
	bgText->setRepeated(true);

	scaleTexture("avenger", 10.0f, 10.0f); // Example: scale by 2x
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

void TextureManager::scaleTexture(std::string key, float scaleX, float scaleY)
{
	sf::Texture* texture = getTexture(key);
	if (texture != nullptr) {
		sf::Vector2u size = texture->getSize();
		texture->setSmooth(true);
		texture->setRepeated(false);
		sf::Sprite sprite(*texture);
		sprite.setScale(scaleX, scaleY);
	}
}