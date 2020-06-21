#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Animation.h"


class Bug
{
public:

	Bug(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, const sf::Vector2f* directionArray, int level);
	Bug(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, const sf::Vector2f* directionArray, int level); // randomized values

	void update(float deltaTime, sf::Vector2f* directionArray);
	void draw(sf::RenderWindow& window);
	sf::FloatRect getGlobalBounds() const;
	int getHealth() const { return health; };
	void setCaught(bool caught);
	void setPosition(float x, float y);
	bool isCaught() const;
	void flee();
	bool isFleeing() const;

	friend std::ostream& operator<<(std::ostream& out, const Bug& c);

private:
	sf::Sprite body;
	Animation animation;
	sf::Sound caughtSound;
	unsigned int row;
	float speed;
	sf::Vector2f direction;
	bool faceRight;
	bool rightSideUp;
	bool caught; // whether the bug is caught and should be destroyed
	bool fleeing; // whether bug is fleeing
	int health; //points to be given to spider if caught
};