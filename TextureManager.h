#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

class TextureManager
{
public:
	static TextureManager* getInstance();
	void testFunction();

	void loadAll();
	sf::Texture* getTexture(std::string);

	void scaleTexture(std::string key, float scaleX, float scaleY);
	sf::Sprite getSprite(const std::string& key, sf::IntRect rect);

private:
	TextureManager() {};
	TextureManager(TextureManager const&) {};
	TextureManager& operator=(TextureManager const&) {};
	static TextureManager* sharedInstance;

	void loadTexture(std::string,std::string);
	std::unordered_map<std::string, sf::Texture*> textureMap;
};