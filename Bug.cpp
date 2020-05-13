#include "Bug.h"
#include <iostream>

int Bug::bugCount = 0;

Bug::Bug(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, const Point pointArray[]) :
	animation(texture, imageCount, switchTime)
{
	bugCount++;
	unsigned int ranCode = rand() % 8;

	switch (ranCode)
	{
	case 0:
		row = 0; // beetle
		health = 5;
		speed = 0.5f;
		break;
	case 1:
		row = 0; // beetle
		health = 6;
		speed = 0.6f;
		break;
	case 2:
		row = 0; // beetle
		health = 7;
		speed = 0.7f;
		break;
	case 3:
		row = 1; // ladybug
		health = 3;
		speed = 0.3f;
		break;
	case 4:
		row = 1; // ladybug
		health = 4;
		speed = 0.4f;
		break;
	case 5:
		row = 1; // ladybug
		health = 5;
		speed = 0.5f;
		break;
	case 6:
		row = 2; // worm
		health = 2;
		speed = 0.2f;
		break;
	case 7:
		row = 2; // worm
		health = 3;
		speed = 0.3f;
		break;
	default:
		std::cout << "Error: constructor failure." << std::endl;
		break;
	}

	faceRight = true;

	//position will be dependent upon the path that is built for the bug
	//initial position is starting point of path
	
	buildPath(pointArray, ranCode);

	//randomize whether the bug walks the path forward or reverse
	int direction = rand() % 2; // how to produce random bool?
	if (direction == 0)
	{
		path.reverse();
	}

	current = path.begin();
	destination = ++path.begin();

	body.setScale(5.0f, 5.0f);
	body.setPosition(path.front()->getPosition());
	body.setTexture(*texture);

	
}

Bug::~Bug()
{
	bugCount--;
	std::cout << "Object Deleted." << std::endl;
}

void Bug::update(const Point* pointArray, float deltaTime)
{
	float destX = (*destination)->getPosition().x;
	float destY = (*destination)->getPosition().y;
	float curPointX = (*current)->getPosition().x;
	float curPointY = (*current)->getPosition().y;

	if (body.getGlobalBounds().contains((*destination)->getPosition()))
	{
		if (next(destination) == path.end()) // bug has completed path
		{
			path.clear();
			unsigned int ranCode = rand() % 8;
			buildPath(pointArray, ranCode); // get a new path
		}
		else
		{
			current = destination;
			destination++;
		}
			destX = (*destination)->getPosition().x;
			destY = (*destination)->getPosition().y;
	}

	sf::Vector2f distance(0.0f, 0.0f);
	distance.x = destX - curPointX;
	distance.y = destY - curPointY;

	if (distance.x < 0)
	{
		faceRight = false;
	}
	
	sf::Vector2f movement(0.0f, 0.0f);
	movement.x += speed * deltaTime;
	movement.y += speed * deltaTime;

	animation.update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(distance.x * deltaTime * speed, distance.y * deltaTime * speed);

}

void Bug::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Bug::buildPath(const Point* pointArray, int dangerCode) // [0-10] are A-K, [11-17] are S1-S7
{

	// edges within range of spider: 0. B to E, 1. B to F, 2. B to G, 3. G to F, 4. G to H,
	// 5. H to C, 6. H to I, 7. D to I

	//choose danger edge
	switch (dangerCode)
	{
	case 0: // push B and E
		path.push_back(pointArray + 1);
		path.push_back(pointArray + 4);
		break;
	case 1: // push B and F
		path.push_back(pointArray + 1);
		path.push_back(pointArray + 5);
		break;
	case 2: // push B and G
		path.push_back(pointArray + 1);
		path.push_back(pointArray + 6);
		break;
	case 3: // push G and F
		path.push_back(pointArray + 5);
		path.push_back(pointArray + 6);
		break;
	case 4: // push G and H
		path.push_back(pointArray + 6);
		path.push_back(pointArray + 7);
		break;
	case 5: // push H and C
		path.push_back(pointArray + 7);
		path.push_back(pointArray + 2);
		break;
	case 6: // push H and I
		path.push_back(pointArray + 7);
		path.push_back(pointArray + 8);
		break;
	case 7: // push D and I
		path.push_back(pointArray + 3);
		path.push_back(pointArray + 8);
		break;
	}

	bool alreadyVisited = false;

	while (!alreadyVisited) 
	{
		auto curPoint = path.front();
		auto iter = path.begin();
		auto iterEnd = path.end();
		const Point* newPoint = curPoint->getRandomConnection();

		while (iter != iterEnd)
		{
			if (newPoint == *iter)
			{
				alreadyVisited = true;
				newPoint = curPoint->getExit();
			}
			iter++;
		}

		path.push_front(newPoint);
	}

	alreadyVisited = false;

	while (!alreadyVisited) 
	{
		auto curPoint = path.back();
		auto iter = path.begin();
		auto iterEnd = path.end();
		const Point* newPoint = curPoint->getRandomConnection(); // get a new point

		while (iter != iterEnd)
		{
			if (newPoint == *iter)
			{
				alreadyVisited = true;
				newPoint = curPoint->getExit();
			}
			iter++;
		}
		path.push_back(newPoint);
	}


	int direction = rand() % 2; // which direction bug walks
	if (direction == 0)
	{
		path.reverse();
	}

	current = path.begin();
	destination = ++path.begin();

	body.setPosition(path.front()->getPosition());
}

int Bug::getHealth() const
{
	return health;
}


std::ostream& operator<<(std::ostream& out, const Bug& c)
{
	out << "Bug Sprite: ";
	switch (c.row)
	{
	case 0:
		out << "Beetle";
		break;
	case 1:
		out << "Ladybug";
		break;
	case 2:
		out << "Worm";
		break;
	default:
		out << "Error";
		break;
	}
	out << std::endl;
	out << "Path: ";

	auto i = c.current;
	while (next(next(i)) !=c.path.end())
	{
		out << "(" << (*i)->getPosition().x << ", " << (*i)->getPosition().y << ") -> ";
		++i;
	}

	++i;
	out << "(" << (*i)->getPosition().x << ", " << (*i)->getPosition().y << ")";

	out << std::endl;

	return out;
}