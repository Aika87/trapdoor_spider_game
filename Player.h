#pragma once
#include "Points.h"
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <map>


class Player
{
public:

	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f* directionArray);
	~Player();

	void update(float deltaTime, sf::Vector2f* directionArray);
	void draw(sf::RenderWindow& window);
	int getHealth() const { return health; };

private:

	/**
		Sets the sprite moving in a random direction

		@param iter iterator to a vector of points
		@param count number of elements in the points vector
		@param deltaTime time between iterations of the game loop
	*/
	void randomMove(std::vector <Points>::iterator iter, int count, float deltaTime);
	void changeDirection();

	//sf::RectangleShape body; 
	sf::Sprite body;
	Animation animation;
	unsigned int row;
	float speed;
	sf::Vector2f direction;
	bool faceRight;
	int health; //points to be given to spider if caught
};