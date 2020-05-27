#include "Point.h"

Point::Point(const sf::Vector2f& position, char name)
{
	this->position = position;
	this->name = name;
	connCount = 0;
}

Point::Point(float x, float y, char name)
{
	this->name = name;
	position = sf::Vector2f(x, y);
	connCount = 0;
}

sf::Vector2f Point::getPosition() const
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

const Point* Point::getRandomConnection() const
{
	srand(unsigned int(time(NULL)));
	int n = rand() % (connCount - 1);

	return connections[n];
}

const Point* Point::getExit() const
{
	return connections[connCount - 1];
}