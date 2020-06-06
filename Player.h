#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <map>

class Player
{
public: 

	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();

	void Update(float deltaTime); 
	void Draw(sf::RenderWindow &window); 

private: 

	void randomMove(std::map <int, int>::iterator iter, int count, float deltaTime);

	//sf::RectangleShape body; 
	sf::Sprite body; 
	Animation animation; 
	unsigned int row; 
	float speed; 
	bool faceRight; 
};
