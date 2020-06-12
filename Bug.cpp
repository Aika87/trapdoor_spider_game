#include "Bug.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

static const unsigned int WINDOW_WIDTH = 2 * sf::VideoMode::getDesktopMode().width / 3;
static const unsigned int WINDOW_HEIGHT = 2 * sf::VideoMode::getDesktopMode().height / 3;

Bug::Bug(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f* directionArray) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;
	rightSideUp = true;
	caught = false;
	direction = *(directionArray + (rand() % 16)); // direction can be any

	body.setTexture(*texture);
	body.setScale(5.0f, 5.0f);
	body.setPosition(10.0f * WINDOW_WIDTH / 160.0f, 70.0f * WINDOW_HEIGHT / 90.0f);

}

Bug::Bug(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f* directionArray) :
	animation(texture, imageCount, switchTime)
{

	faceRight = true;
	rightSideUp = true;
	caught = false;
	direction = *(directionArray + (rand() % 16)); // direction can be any

	unsigned int ranCode = rand() % 8;

	switch (ranCode)
	{
	case 0:
		row = 0; // beetle
		health = 5;
		this->speed = 500.0f;
		break;
	case 1:
		row = 0; // beetle
		health = 6;
		this->speed = 600.0f;
		break;
	case 2:
		row = 0; // beetle
		health = 7;
		this->speed = 700.0f;
		break;
	case 3:
		row = 1; // ladybug
		health = 3;
		this->speed = 300.0f;
		break;
	case 4:
		row = 1; // ladybug
		health = 4;
		this->speed = 400.0f;
		break;
	case 5:
		row = 1; // ladybug
		health = 5;
		this->speed = 500.0f;
		break;
	case 6:
		row = 2; // worm
		health = 2;
		this->speed = 200.0f;
		break;
	case 7:
		row = 2; // worm
		health = 3;
		this->speed = 300.0f;
		break;
	default:
		std::cout << "Error: constructor failure." << std::endl;
		break;
	}

	switchTime = 100.0f / speed;
	animation.setSwitchTime(switchTime);
	body.setTexture(*texture);
	body.setScale(5.0f, 5.0f);

	// set position anywhere inside the boundary
	unsigned int topBound = 60 * WINDOW_HEIGHT / 90;
	body.setPosition(rand() % WINDOW_WIDTH, rand() % (WINDOW_HEIGHT - topBound) + topBound);

}


Bug::~Bug()
{
}

void Bug::update(float deltaTime, sf::Vector2f* directionArray)
{
	float posX = body.getPosition().x,
		posY = body.getPosition().y;

	// Collision - stay inside an 8 sided polygon with vertices at:
	// (0, 50), (70, 50), (70, 60), (125, 60), (125, 50), (160, 50), (160, 90), (0, 90)
	if (caught)
	{
		// flip upsidedown
		rightSideUp = false;
		// switch time is shortened
		animation.setSwitchTime(animation.getSwitchTime() / 1.1f);
	}
	else
	{
		if ((posY + body.getGlobalBounds().height) > WINDOW_HEIGHT) // against bottom border, go up
		{
			// negative y: indexes [9-15]
			direction = *(directionArray + (rand() % 7 + 9));
		}
		else if (posX < 0.0f) // against left border, go right
		{
			// positive x component: indexes [0-3] and [13-15]
			int coinFlip = rand() % 2;
			direction = (coinFlip == 1) ? *(directionArray + rand() % 4) : *(directionArray + rand() % 3 + 13);
		}
		else if (posY < 45.0f * WINDOW_HEIGHT / 90.0f) // against top border, go down
		{
			// positive y component: indexes [1-7]
			direction = *(directionArray + rand() % 7 + 1);
		}
		else if ((posX + body.getGlobalBounds().width) > WINDOW_WIDTH) // against right border, go left
		{
			// negative x: indexes [5-11]
			direction = *(directionArray + rand() % 7 + 5);
		}
		else if (posY < 60.0f * WINDOW_HEIGHT / 90.0f &&
			(posX + body.getGlobalBounds().width) > 70.0f * WINDOW_WIDTH / 160.0f &&
			posX < 125.0f * WINDOW_WIDTH / 160.0f) // collided with hatch
		{
			if (posX > 120.0f * WINDOW_WIDTH / 160.0f) // against right side of hatch, go right
			{
				// positive x component: indexes [0-3] and [13-15]
				int coinFlip = rand() % 2;
				direction = (coinFlip == 1) ? *(directionArray + rand() % 4) : *(directionArray + rand() % 3 + 13);
			}
			else if (posY > 55.0f * WINDOW_HEIGHT / 90.0f) // against bottom of hatch, go down
			{
				// positive y component: indexes [1-7]
				direction = *(directionArray + rand() % 7 + 1);
			}
			else if ((posX + body.getGlobalBounds().width) < 75.0f * WINDOW_WIDTH / 160.0f) // against left side of hatch, go left
			{
				// negative x: indexes [5-11]
				direction = *(directionArray + rand() % 7 + 5);
			}
		}
		if (direction.x < 0)
		{
			faceRight = false;
		}
		else
		{
			faceRight = true;
		}

		body.move(direction * speed * deltaTime);
	}

	animation.update(row, deltaTime, faceRight, rightSideUp);
	body.setTextureRect(animation.uvRect);
}

void Bug::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

sf::FloatRect Bug::getGlobalBounds() const
{
	return body.getGlobalBounds();
}

void Bug::setCaught(bool caught)
{
	this->caught = caught;
}

bool Bug::isCaught() const
{
	return caught;
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
	out << "Health: " << c.health << std::endl;
	out << "Speed: " << c.speed << std::endl;
	
	out << std::endl;

	return out;
}