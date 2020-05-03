#pragma once

#include <SFML\Graphics.hpp>
#include <map>
#include <time.h>
#include <stdlib.h>

void randomMove(sf::Sprite* sprite, float deltaTime)
{
	sf::Vector2f position = sprite->getPosition(); 
	std::map <int, int> slope{ {1,2}, {2,-1}, {1,-3} };
	float speed = 0.1; 
	auto iter = slope.begin();

	/*float totalTime = 0.0; 
	totalTime += deltaTime; 
	float switchTime = .10; */

	//if (totalTime >= switchTime)
	//{
	//	totalTime -= switchTime;
		
		srand(time(NULL));
		int newDest = rand() % 3;

		if (newDest == 1)
			sprite->move(speed * iter->first, speed * iter->second);

		if (newDest == 2)
		{
			++iter; 
			sprite->move(speed * iter->first, speed * iter->second);
		}

		if (newDest == 3)
		{
			++iter;
			sprite->move(speed * iter->first, speed * iter->second);
		}

	//}
	
}