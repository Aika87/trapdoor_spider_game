#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"

class Spider
{
public:
	Spider(sf::Texture* texture, sf::Vector2u imageCount,
		float switchTime);
	~Spider();

	//	animation update function: 
	//	start in resting position 
	//	shift resting position on left/right (change row)
	//	lunge on spacebar: loop through frames 1-5, lingering on frame 4 and 5, 
	//		then if bug is caught: show the closed hatch without legs for a few seconds, update health
	//		if bug isn't caught, go back to resting position
	bool lunge(float deltaTime, bool* delayed);

	/**
		Shifts the resting pose of the spider right or left

		@param direction the direction to shift, -1 for left, 1 for right
	*/
	void shift(int direction);
	unsigned int getRow() const;
	void setRow(unsigned int newRow);

	void draw(sf::RenderWindow& window);
	void setScale(float x, float y) { body.setScale(x, y); };
	void setPosition(float x, float y) { body.setPosition(x, y); };


private:
	sf::Sprite body;
	Animation animation;
	unsigned int row;
};