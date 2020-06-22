#include "Spider.h"
#include <iostream>

Spider::Spider(sf::Texture* texture, const sf::Vector2u& imageCount, 
	float switchTime) :
	animation(texture, imageCount, switchTime)
{
	row = 2;

	body.setTexture(*texture);

	sf::Vector2u image = animation.getCurrentImage();
	image.y = row;
	animation.setCurrentImage(image);
	animation.uvRect.top = image.y * animation.uvRect.height;
	body.setTextureRect(animation.uvRect);
}

void Spider::draw(sf::RenderWindow& window) const 
{
	window.draw(body);
}

bool Spider::lunge(float deltaTime, bool* delayed)
{
	unsigned int prevImage = animation.getCurrentImage().x;
	animation.update(row, deltaTime, false, true);
	unsigned int curImage = animation.getCurrentImage().x;
	body.setTextureRect(animation.uvRect);

	switch (curImage)
	{
	case 0:
		if (prevImage != 0) 
		{
			animation.setSwitchTime(0.05f); // had to hardcode switchTime, bad form
			*delayed = false;
			return false;
		}
		break;
	case 4:
		if (!(*delayed))
		{
			animation.setSwitchTime(1.5f); // hardcoding, bad form
			*delayed = true;
		}
		break;
	}
	return true;
}

void Spider::shift(int direction)
{
	row += direction;
	sf::Vector2u image = animation.getCurrentImage();
	image.y = row;
	animation.setCurrentImage(image);
	animation.uvRect.top = image.y * animation.uvRect.height;

	//set new body rect
	body.setTextureRect(animation.uvRect);
}

void Spider::resetAnimation()
{
	row = 2;
	animation.setCurrentImage(sf::Vector2u(0, row));
	animation.setSwitchTime(0.05f);
}

sf::Vector2u Spider::getCurrentImage() const
{
	return animation.getCurrentImage();
}

sf::FloatRect Spider::getGlobalBounds() const
{
	return body.getGlobalBounds();
}

Spider::~Spider()
{
}