#include "AnimatedButton.h"

AnimatedButton::AnimatedButton(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) :
	animation(texture, imageCount, switchTime)
{
	body.setTexture(*texture);
}

void AnimatedButton::setPosition(float x, float y)
{
	body.setPosition(x, y);
}

void AnimatedButton::setScale(float x, float y)
{
	body.setScale(x, y);
}

void AnimatedButton::update(float deltaTime)
{
	animation.update(0, deltaTime, false, true);
	body.setTextureRect(animation.uvRect);
}

void AnimatedButton::draw(sf::RenderWindow& window)
{
	window.draw(body);
}
