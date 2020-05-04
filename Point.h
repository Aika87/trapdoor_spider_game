#pragma once
#include <SFML\Graphics.hpp>

const int CONNECTION_CAP = 6;

class Point
{
public:
	Point(const sf::Vector2f& position);
	Point(float x, float y);
	sf::Vector2f getPosition();
	void setPosition(float x, float y);
	void connect(const Point& point); 

private:
	sf::Vector2f position;
	const Point *connections[CONNECTION_CAP];
	int connCount;

	friend class Bug;
};