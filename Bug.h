#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Animation.h"

enum bugState { WALKING = 0, FLEEING = 1, CAUGHT = 2 };

class Bug
{
public:

	Bug(sf::Texture* texture, const sf::Vector2u& imageCount, float switchTime, float speed, const sf::Vector2f* directionArray, int level);
	Bug(sf::Texture* texture, const sf::Vector2u& imageCount, float switchTime, const sf::Vector2f* directionArray, int level); // randomized values

	void update(float deltaTime, const sf::Vector2f* directionArray);
	void draw(sf::RenderWindow& window) { window.draw(body); };
	sf::FloatRect getGlobalBounds() const { return body.getGlobalBounds(); };
	int getHealth() const { return health; };
	void setState(int n) { state = bugState(n); };
	bugState getState() const { return state; };

	friend std::ostream& operator<<(std::ostream& out, const Bug& c);

private:
	sf::Sprite body;
	Animation animation;
	unsigned int row;
	float speed;
	sf::Vector2f direction;
	bool faceRight;
	bool rightSideUp;
	int health; //points to be given to spider if caught
	bugState state;
	
};