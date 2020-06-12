#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount)
{
	this->imageCount = imageCount;
	currentImage.x = 0;
	totalTime = 0.0f;
	switchTime = 0.0f;

	uvRect.width = texture->getSize().x / imageCount.x;
	uvRect.height = texture->getSize().y / imageCount.y;
}

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / imageCount.x;
	uvRect.height = texture->getSize().y / imageCount.y;
}

void Animation::update(int row, float deltaTime, bool faceRight, bool rightSideUp)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	uvRect.top = currentImage.y * uvRect.height;

	if (faceRight)
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
	else
	{
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	if (rightSideUp)
	{
		uvRect.top = currentImage.y * uvRect.height;
		uvRect.height = abs(uvRect.height);
	}
	else
	{
		uvRect.top = (currentImage.y + 1) * abs(uvRect.height);
		uvRect.height = -abs(uvRect.height);
	}
}

void Animation::updateManually(int row, int increase)
{
	currentImage.y = row;

	currentImage.x = increase;

	if (currentImage.x >= imageCount.x)
	{
		currentImage.x = 0;
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;

}

sf::Vector2u Animation::getCurrentImage() const
{
	return currentImage;
}

void Animation::setCurrentImage(sf::Vector2u rect)
{
	currentImage = rect;
}

float Animation::getSwitchTime() const
{
	return switchTime;
}

void Animation::setSwitchTime(float switchTime)
{
	this->switchTime = switchTime;
}

Animation::~Animation()
{
}