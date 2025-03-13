#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Entity
{
public:
	Entity();
	void setTexture(sf::Texture& texture);
	sf::Sprite* getSprite();

	static Entity* createEntity(sf::Texture* tex, float x, float y);

private:
	sf::Sprite mSprite;
	sf::Texture mTexture;
};
