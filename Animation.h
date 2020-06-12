#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();

	void update(int row, float deltaTime, bool faceRight, bool rightSideUp);
	sf::Vector2u getCurrentImage() const;
	void setCurrentImage(sf::Vector2u rect);
	float getSwitchTime() const;
	void setSwitchTime(float switchTime);

	sf::IntRect uvRect; // rectangular subset of the texture

private:
	sf::Vector2u imageCount; // number of images you wish to cycle through
	sf::Vector2u currentImage;
	float totalTime;
	float switchTime; // time to switch between frames
};