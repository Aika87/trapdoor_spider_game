#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();

	void update(int row, float deltaTime);

	void update(int row, int col, float deltaTime); 

	sf::IntRect uvRect; // rectangular subset of the texture

private:
	sf::Vector2u imageCount; // number of images you wish to cycle through
	sf::Vector2u currentImage;
	float totalTime;
	float switchTime; // time to switch between frames

};