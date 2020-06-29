#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class AnimatedButton
{
public:
	AnimatedButton(sf::Texture* texture, const sf::Vector2u& imageCount, float switchTime);

	void setPosition(float x, float y);
	void setScale(float x, float y);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	sf::Sprite body;
	Animation animation;
};