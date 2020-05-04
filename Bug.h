#pragma once
#include <SFML\Graphics.hpp>
#include <list>
#include "Animation.h"
#include "Point.h"

class Bug
{
public:
	Bug(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, const Point* pointArray);
	~Bug();

	void update(float deltaTime);
	void draw(sf::RenderWindow window);
	void buildPath(const Point* pointArray);
	int caughtOrFlee(bool inLunge); // if the bug is caught, it returns the score worth

private:
	std::vector<Point> Path; // list of points that make up the bug's path
	Animation animation;
	unsigned int row;
	float speed;
	sf::Sprite body;
	int worth;
	bool faceRight;
	
	

};