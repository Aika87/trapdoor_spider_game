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
	//	lunge on spacebar: loop through frames 1-5, lingering on frame 5, 
	//		then if bug is caught: show the closed hatch without legs for a few seconds, update health
	//		if bug isn't caught, go back to resting position
	void update(float deltaTime);
	void lunge(float deltaTime);


private:
	sf::Sprite body;
	Animation animation;
	unsigned int row;
	bool inLunge;
};