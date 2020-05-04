#include "Bug.h"

Bug::Bug(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	//position will be dependent upon the path that is built for the bug
}

void Bug::buildPath()
{
	//choose start and end
	srand(time(NULL));
	int start = rand() % 7;
	int end = rand() % 7;

	switch (start) 
	{
	case 0:
		Path.push_front(&pointS1);
	}
}