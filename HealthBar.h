#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"

class HealthBar
{
public:
	HealthBar(sf::Texture* texture, sf::Vector2u imageCount,
		float switchTime);

	int getHealth() const;

	void draw(sf::RenderWindow& window);
	void update(int health, float deltaTime);
	void reset();
	void setScale(float x, float y) { body.setScale(x, y); };
	void setPosition(float x, float y) { body.setPosition(x, y); };
	

private:
	int health;
	sf::Sprite body;
	Animation animation;
};