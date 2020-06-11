#include "HealthBar.h"

HealthBar::HealthBar(sf::Texture* texture, sf::Vector2u imageCount,
	float switchTime) :
	animation(texture, imageCount, switchTime)
{
	health = 15;
	body.setTexture(*texture);

	animation.setCurrentImage(sf::Vector2u(0, 0));
	body.setTextureRect(animation.uvRect);
}

int HealthBar::getHealth() const
{
	return health;
}

void HealthBar::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void HealthBar::update(int health, float deltaTime)
{
	this->health += health;
	if (this->health <= 0) // game over, health is gone
	{
		animation.setCurrentImage(sf::Vector2u(15, 0));
		//TODO: create game over method
	}
	else if (this->health >= 15) // health restored fully
	{
		health = 15;
		animation.setCurrentImage(sf::Vector2u(0, 0));
	}
	else // health is between 0 and 15
	{
		// jump sprite back by health added
		int x = animation.getCurrentImage().x - health;
		animation.setCurrentImage(sf::Vector2u(x, 0));
	}

	animation.update(0, deltaTime, false);
	body.setTextureRect(animation.uvRect);
}

void HealthBar::reset()
{
	health = 15;
	animation.setCurrentImage(sf::Vector2u(0, 0));
}