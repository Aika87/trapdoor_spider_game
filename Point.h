#pragma once
#include <SFML\Graphics.hpp>

const int CONNECTION_CAP = 6;

class Point
{
public:
	Point(const sf::Vector2f& position, char name);
	Point(float x, float y, char name);

	/**
		returns the position of a point

		@return a sf::Vector2f of the position
	*/
	sf::Vector2f getPosition() const;
	void setPosition(float x, float y);

	/**
		connects a point to another point by placing a pointer in its 
		connection array

		@param point the point to connect to
	*/
	void connect(const Point& point);

	/**
		returns a pointer to a random connected point

		@return pointer to a connected point
	*/
	const Point* getRandomConnection() const;

	/**
		returns a pointer to an offscreen point (last element in connection array)

		@return pointer to an exit
	*/
	const Point* getExit() const;

	char getName() const { return name; };

private:
	sf::Vector2f position;
	const Point* connections[CONNECTION_CAP]; // array of pointers to other points, last element is offscreen
	int connCount;
	char name;

	friend class Bug;
};