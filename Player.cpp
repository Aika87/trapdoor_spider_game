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

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed):
	animation(texture, imageCount, switchTime)
{
	this->speed = speed; 
	row = 0; 
	faceRight = true; 

	body.setTexture(*texture);
	body.setScale(sf::Vector2f(5.0f, 5.0f));
	body.setPosition(100.0f, 350.0f);
	
}

Player::~Player()
{ 
}


void Player::Update(float deltaTime)
{
	animation.update(0, deltaTime, true);
	body.setTextureRect(animation.uvRect);

	//Random Movement

	//std::map <int, int> slope{ {-1,2}, {2,-1}, {1,-3}, {-5,2}, {1,1}, {2,2} };
	Points p1(-1, 2); 
	Points p2(2, -1);
	Points p3(1, -3);
	Points p4(-5, 2);
	Points p5(1, 1);
	Points p6(-4, 7);
	Points p7(2, 5);
	Points p8(1, -3);
	Points p9(5, -7);
	Points p10(-1, 1);

	vector <Points> slope{ p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 };
	int numOfSlopes = 10;
	vector <Points>::iterator iter = slope.begin();

	randomMove(iter, numOfSlopes, deltaTime);
	

	//Collision 
	if (body.getPosition().x <= 0.0f)
	{
		iter = slope.begin();
		body.setPosition(0.0f, body.getPosition().y);

		body.move((speed * 3 * deltaTime), (speed * 2 * deltaTime));
		//randomMove(iter, numOfSlopes, deltaTime);
	}

	if (body.getPosition().y < 200.0f)
	{
		iter = slope.begin();
		body.setPosition(body.getPosition().x, 200.0f);

		randomMove(iter, numOfSlopes, deltaTime);
	}


	if ((body.getPosition().y + body.getGlobalBounds().height) > 480.0f)
	{
		iter = slope.begin();
		body.setPosition(body.getPosition().x, (480.0f - body.getGlobalBounds().height));

		//body.move((speed * 3 * deltaTime), (speed * -2 * deltaTime));
		randomMove(iter, numOfSlopes, deltaTime);

	}

	if ((body.getPosition().x + body.getGlobalBounds().width) > 800.0f)
	{
		iter = slope.begin();
		body.setPosition((800.0f - body.getGlobalBounds().width), body.getPosition().y);

		randomMove(iter, numOfSlopes, deltaTime);
	}
	
}

void Player::Draw(sf::RenderWindow &window)
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