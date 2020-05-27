#pragma once
#include <SFML\Graphics.hpp>
#include <list>
#include <iostream>
#include "Animation.h"
#include "Point.h"

class Bug
{
public:
	static int bugCount;

	Bug(sf::Texture* texture, sf::Vector2u imageCount, 
		float switchTime, const Point pointArray[]);
	~Bug();

	/**
		updates the animation of the bug

		@param deltaTime the time between frames
	*/
	void update(const Point* pointArray, float deltaTime);

	/**
		draws the body sprite

		@param window the render window
	*/
	void draw(sf::RenderWindow& window);

	/**
		creates a random path for the bug to follow

		@param pointArray an array of all points
		@param dangerCode a random number that chooses the segment within the 
		range of the spider
	*/
	void buildPath(const Point* pointArray, int dangerCode);

	/**
		creates a path from the given list of points

		@param pointArray an array of the desired points
	*/
	void setPath(std::list<const Point*> path);

	/**
		returns the amount of health the bug will add to the spider when caught

		@return the health worth of the bug
	*/
	int getHealth() const;
	//int caughtOrFlee(bool inLunge); // if the bug is caught, it returns the score worth
	
	friend std::ostream& operator<<(std::ostream& out, const Bug& c);

private:
	std::list<const Point*> path; // list of points that make up the bug's path, [0-10] are onscreen [11-17] are offscreen
	std::list<const Point*>::iterator destination; // next point that bug will go to
	std::list<const Point*>::iterator current; // point where bug is currently
	Animation animation;
	unsigned int row;
	float speed;
	sf::Sprite body;
	int health; //points to be given to spider if caught
	bool faceRight;
	
	

};