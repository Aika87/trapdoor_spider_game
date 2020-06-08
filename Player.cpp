#include "Player.h"
#include "Points.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

static const unsigned int WINDOW_WIDTH = 2 * sf::VideoMode::getDesktopMode().width / 3;
static const unsigned int WINDOW_HEIGHT = 2 * sf::VideoMode::getDesktopMode().height / 3;

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f* directionArray) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;
	direction = *(directionArray + (rand() % 16)); // direction can be any

	body.setTexture(*texture);
	body.setScale(5.0f, 5.0f);
	body.setPosition(10.0f * WINDOW_WIDTH / 160.0f, 70.0f * WINDOW_HEIGHT / 90.0f);

}

Player::~Player()
{
}

void Player::update(float deltaTime, sf::Vector2f* directionArray)
{
	float posX = body.getPosition().x,
		posY = body.getPosition().y;
	int randIdx;

	// Collision - stay inside an 8 sided polygon with vertices at:
	// (0, 50), (70, 50), (70, 60), (125, 60), (125, 50), (160, 50), (160, 90), (0, 90)

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

	animation.update(0, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}

void Player::changeDirection()
{
	float posX = body.getPosition().x,
		posY = body.getPosition().y,
		hatchBottom = 60.0f * WINDOW_HEIGHT / 90.0f,
		hatchLeft = 70.0f * WINDOW_WIDTH / 160.0f,
		hatchRight = 125.0f * WINDOW_WIDTH / 160.0f;
	int randIdx;

	// Collision - stay inside an 8 sided polygon with vertices at:
	// (0, 50), (70, 50), (70, 60), (125, 60), (125, 50), (160, 50), (160, 90), (0, 90)

	if ((posY + body.getGlobalBounds().height) > WINDOW_HEIGHT) // against bottom border, go up
	{
		// negative y: indexes [9-15]
		randIdx = rand() % 7 + 9;
	}
	else if (posX < 0.0f) // against left border, go right
	{
		// positive x component: indexes [0-3] and [13-15]
		int coinFlip = rand() % 2;
		randIdx = (coinFlip == 1) ? rand() % 4 : rand() % 3 + 13;
	}
	else if (posY < 50.0f * WINDOW_HEIGHT / 90.0f) // against top border, go down
	{
		// positive y component: indexes [1-7]
		randIdx = rand() % 7 + 1;
	}
	else if ((posX + body.getGlobalBounds().width) > WINDOW_WIDTH) // against right border, go left
	{
		// negative x: indexes [5-11]
		randIdx = rand() % 7 + 5;
		faceRight = false;
	}
	else if (posY < hatchBottom &&
		posX > hatchLeft &&
		posX < hatchRight)
	{
		if (posX > 120.0f * WINDOW_WIDTH / 160.0f) // against right side of hatch
		{
			// positive x component: indexes [0-3] and [13-15]
			int coinFlip = rand() % 2;
			randIdx = (coinFlip == 1) ? rand() % 4 : rand() % 3 + 13;
		}
		else if (posY > 55.0f * WINDOW_HEIGHT / 90.0f) // against bottom of hatch
		{
			// positive y component: indexes [1-7]
			randIdx = rand() % 7 + 1;
		}
		else if (posX < 75.0f * WINDOW_WIDTH / 160.0f) // against left side of hatch
		{
			// negative x: indexes [5-11]
			randIdx = rand() % 7 + 5;
			faceRight = false;
		}
	}
	//direction = unitCircle[randIdx];
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::randomMove(vector <Points>::iterator iter, int count, float deltaTime)
{
	srand(time(NULL));
	int newDest = rand() % count;
	cout << "newDest -> " << newDest << endl;


	for (int i = 0; i < newDest; ++i)
	{
		++iter;
	}

	body.move((speed * iter->getX() * deltaTime), (speed * iter->getY() * deltaTime));

}