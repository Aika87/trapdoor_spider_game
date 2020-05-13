#include "Spider.h"

Spider::Spider(sf::Texture* texture, sf::Vector2u imageCount, 
	float switchTime) :
	animation(texture, imageCount, switchTime)
{
	row = 0;
}

void Spider::update(float deltaTime)
{
	// sf::Keyboard::isKeyPressed(key) is a function to see of a particular key was pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		row != 0 )
	{
		row--;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		row < 4)
	{
		row++;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		lunge(deltaTime);
	}
}

void Spider::lunge(float deltaTime)
{

}