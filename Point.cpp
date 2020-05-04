#include "Point.h"

Point::Point(const sf::Vector2f& position)
{
	this->position = position;
	connCount = 0;
}

Point::Point(float x, float y)
{
	position = sf::Vector2f(x, y);
	connCount = 0;
}

sf::Vector2f Point::getPosition()
{
	return position;
}

void Point::setPosition(float x, float y)
{
	position = sf::Vector2f(x, y);
}

void Point::connect(const Point& point)
{
	connections[connCount] = &point;
	connCount++;
}

const Point* Point::getRandomConnection()
{
	srand(unsigned int(time(NULL)));
	int n = rand() % connCount;

	return connections[n];
}