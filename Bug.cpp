#include "Bug.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

static const unsigned int WINDOW_WIDTH = 2 * sf::VideoMode::getDesktopMode().width / 3;
static const unsigned int WINDOW_HEIGHT = 2 * sf::VideoMode::getDesktopMode().height / 3;
static const sf::Vector2f BURROW(98.0f * WINDOW_WIDTH / 160.0f, 53.0f * WINDOW_HEIGHT / 90.0f);

Bug::Bug(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, const sf::Vector2f* directionArray, int level) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	rightSideUp = faceRight = true;
	fleeing = caught = false;
	direction = *(directionArray + (rand() % 16)); // direction can be any

	body.setTexture(*texture);
	body.setScale(5.0f, 5.0f);
	body.setPosition(10.0f * WINDOW_WIDTH / 160.0f, 70.0f * WINDOW_HEIGHT / 90.0f);

}

Bug::Bug(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, const sf::Vector2f* directionArray, int level) :
	animation(texture, imageCount, switchTime)
{

	faceRight = true;
	rightSideUp = true;
	caught = false;
	direction = *(directionArray + (rand() % 16)); // direction can be any

	// level must determine sprite and speed: 
	// level 1: 100% worms speed 2
	// level 2: 75% worms speed 2, 25% worms speed 3
	// level 3: 25% worms speed 2, 50% worms speed 3, 25% lady speed 4
	// level 4: 25% worms speed 3, 50% lady speed 4, 25% lady speed 5
	// level 5: 25% lady speed 4, 50% lady speed 5, 25% beetle speed 6
	// level 6: 25% lady speed 5, 50% beetle speed 6, 25% beetle speed 7
	// level 7: 25% beetle speed 6, 50% beetle speed 7, 25% beetle speed 8
	// level 8: 50% beetle speed 7, 50% beetle speed 8
	// level 9: 100% beetle speed 8
	// after 10 it should be a beetle whose speed = level * 10

	unsigned int ranCode = rand() % 4;

	switch (level)
	{
	case 1:// level 1: 100% worms speed 2
		row = 2; // worm
		health = 2;
		this->speed = 200.0f;
		break;
	case 2:// level 2: 75% worms speed 2, 25% worms speed 3
		if (ranCode == 0)
		{
			row = 2; // worm
			health = 3;
			this->speed = 300.0f;
		}
		else
		{
			row = 2; // worm
			health = 2;
			this->speed = 200.0f;
		}
		break;
	case 3:// level 3: 25% worms speed 2, 50% worms speed 3, 25% lady speed 4
		if (ranCode == 0)
		{
			row = 2; // worm
			health = 2;
			this->speed = 200.0f;
		}
		else if (ranCode == 1)
		{
			row = 1; // ladybug
			health = 4;
			this->speed = 400.0f;
		}
		else
		{
			row = 2; // worm
			health = 3;
			this->speed = 300.0f;
		}
		break;
	case 4:// level 4: 25% worms speed 3, 50% lady speed 4, 25% lady speed 5
		if (ranCode == 0)
		{
			row = 2; // worm
			health = 3;
			this->speed = 300.0f;
		}
		else if (ranCode == 1)
		{
			row = 1; // ladybug
			health = 5;
			this->speed = 500.0f;
		}
		else
		{
			row = 1; // ladybug
			health = 4;
			this->speed = 400.0f;
		}
		break;
	case 5:// level 5: 25% lady speed 4, 50% lady speed 5, 25% beetle speed 6
		if (ranCode == 0)
		{
			row = 1; // ladybug
			health = 4;
			this->speed = 400.0f;
		}
		else if (ranCode == 1)
		{
			row = 0; // beetle
			health = 6;
			this->speed = 600.0f;
		}
		else
		{
			row = 1; // ladybug
			health = 5;
			this->speed = 500.0f;
		}
		break;
	case 6:// level 6: 25% lady speed 5, 50% beetle speed 6, 25% beetle speed 7
		if (ranCode == 0)
		{
			row = 1; // ladybug
			health = 5;
			this->speed = 500.0f;
		}
		else if (ranCode == 1)
		{
			row = 0; // beetle
			health = 7;
			this->speed = 700.0f;
		}
		else
		{
			row = 0; // beetle
			health = 6;
			this->speed = 600.0f;
		}
		break;
	case 7:// level 7: 25% beetle speed 6, 50% beetle speed 7, 25% beetle speed 8
		if (ranCode == 0)
		{
			row = 0; // beetle
			health = 6;
			this->speed = 600.0f;
		}
		else if (ranCode == 1)
		{
			row = 0; // beetle
			health = 8;
			this->speed = 800.0f;
		}
		else
		{
			row = 0; // beetle
			health = 7;
			this->speed = 700.0f;
		}
		break;
	case 8:// level 8: 50% beetle speed 7, 50% beetle speed 8
		if (ranCode > 2)
		{
			row = 0; // beetle
			health = 7;
			this->speed = 700.0f;
		}
		else
		{
			row = 0; // beetle
			health = 8;
			this->speed = 800.0f;
		}
		break;
	case 9:// level 9: 100% beetle speed 8
		row = 0; // beetle
		health = 8;
		this->speed = 800.0f;
		break;
	default:
		break;
	}



	//unsigned int ranCode = rand() % 8;

	//switch (ranCode)
	//{
	//case 0:
	//	row = 0; // beetle
	//	health = 5;
	//	this->speed = 500.0f;
	//	break;
	//case 1:
	//	row = 0; // beetle
	//	health = 6;
	//	this->speed = 600.0f;
	//	break;
	//case 2:
	//	row = 0; // beetle
	//	health = 7;
	//	this->speed = 700.0f;
	//	break;
	//case 3:
	//	row = 1; // ladybug
	//	health = 3;
	//	this->speed = 300.0f;
	//	break;
	//case 4:
	//	row = 1; // ladybug
	//	health = 4;
	//	this->speed = 400.0f;
	//	break;
	//case 5:
	//	row = 1; // ladybug
	//	health = 5;
	//	this->speed = 500.0f;
	//	break;
	//case 6:
	//	row = 2; // worm
	//	health = 2;
	//	this->speed = 200.0f;
	//	break;
	//case 7:
	//	row = 2; // worm
	//	health = 3;
	//	this->speed = 300.0f;
	//	break;
	//default:
	//	std::cout << "Error: constructor failure." << std::endl;
	//	break;
	//}

	switchTime = 100.0f / speed;
	animation.setSwitchTime(switchTime);
	body.setTexture(*texture);
	body.setScale(5.0f, 5.0f);

	// set position anywhere inside the boundary
	unsigned int topBound = 60 * WINDOW_HEIGHT / 90;
	body.setPosition(rand() % WINDOW_WIDTH, rand() % (WINDOW_HEIGHT - topBound) + topBound);

}

void Bug::update(float deltaTime, sf::Vector2f* directionArray)
{
	float posX = body.getPosition().x,
		posY = body.getPosition().y;

	// Collision - stay inside an 8 sided polygon with vertices at:
	// (0, 50), (70, 50), (70, 60), (125, 60), (125, 50), (160, 50), (160, 90), (0, 90)
	if (caught && rightSideUp)
	{
		// flip upsidedown
		rightSideUp = false;
		// switch time is shortened
		animation.setSwitchTime(animation.getSwitchTime() / 5.0f);
	}
	else if (fleeing && !caught) // fleeing and not already in a fleeing direction
	{
		if (posX >= BURROW.x && (direction.x < 0.0f || direction.y < 0.0f)) // bug is to the right or directly underneath hatch, going left or up
		{
			// x must be negative, y must be less than or equal to zero
			int randInt = rand() % 5 + 12; // indexes [12-15] and [0]
			if (randInt == 16)
			{
				direction = *directionArray;
			}
			else
			{
				direction = *(directionArray + randInt);
			}
		}
		else if (posX < BURROW.x && (direction.x > 0.0f || direction.y < 0.0f)) // bug is to the left of hatch, going right or up
		{
			// x must be positive, y must be less than or equal to zero
			direction = *(directionArray + (rand() % 5 + 8)); // indexes [8-12]
		}
		body.move(direction * speed * deltaTime);
	}
	else if (!fleeing && !caught)
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
		body.move(direction * speed * deltaTime);
	}
	if (direction.x <= 0)
	{
		faceRight = false;
	}
	else
	{
		faceRight = true;
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

void Bug::setPosition(float x, float y)
{
	body.setPosition(x, y);
}

bool Bug::isCaught() const
{
	return caught;
}

void Bug::flee()
{
	fleeing = true;
}

bool Bug::isFleeing() const
{
	return fleeing;
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