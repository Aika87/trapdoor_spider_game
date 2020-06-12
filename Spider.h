#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"

class Spider
{
public:
	Spider(sf::Texture* texture, sf::Vector2u imageCount,
		float switchTime);
	~Spider();

	/**
		Animation update function. The spider starts in center resting position,
		which can shift with the left/right keys.
		When the space bar is pressed, the spider loops through frames 1-5, 
		lingering on frame 4 and 5. Then if the bug is caught update health.

		@param deltaTime the time between game loop iterations
		@param[out] delayed whether the spider's switch time has been extended

		@return bool true if spider is still in lunge animation
	*/
	bool lunge(float deltaTime, bool* delayed);

	/**
		Shifts the resting pose of the spider right or left

		@param direction the direction to shift, -1 for left, 1 for right
	*/
	void shift(int direction);
	unsigned int getRow() const;
	sf::Vector2u getCurrentImage() const;
	sf::FloatRect getGlobalBounds() const;
	void setRow(unsigned int newRow);
	void resetAnimation();

	void draw(sf::RenderWindow& window);
	void setScale(float x, float y) { body.setScale(x, y); };
	void setPosition(float x, float y) { body.setPosition(x, y); };


private:
	sf::Sprite body;
	Animation animation;
	unsigned int row;
};