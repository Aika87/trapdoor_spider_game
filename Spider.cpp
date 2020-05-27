#include "Spider.h"

Spider::Spider(sf::Texture* texture, sf::Vector2u imageCount, 
	float switchTime) :
	animation(texture, imageCount, switchTime)
{
	row = 2;

	body.setTexture(*texture);
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

	animation.update(row, deltaTime, false);
	body.setTextureRect(animation.uvRect);
}

void Spider::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Spider::lunge(float deltaTime)
{
	animation.update(row, deltaTime, false);
}

Spider::~Spider()
{
}