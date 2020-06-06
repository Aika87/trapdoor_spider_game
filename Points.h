#pragma once
#include <SFML\Graphics.hpp>

class Points
{
public:

	Points(int newX, int newY)
	{
		x = newX; 
		y = newY; 
	}

	int getX() { return x; } const 
	int getY() { return y; } const

	void setX(int newX) { x = newX; }
	void setY(int newY) { y = newY; }

	//~Points();

private:

	int x; 
	int y; 
};