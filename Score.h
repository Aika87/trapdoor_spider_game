#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"

class Score
{
public:

	Score(sf::Texture* textureScore, sf::Vector2u imageCountScore, sf::Texture* textureLevel, sf::Vector2u imageCountLevel,
		const int bgWidth, sf::Vector2f bgPosition, const int lvWidth, sf::Vector2f lvPosition, const int difference);
	~Score(); 
	
	void setScore(int newScore); 
	void setLevel(int newLevel); 

	int getScore() const; 
	int getLevel() const; 
	
	void updateScore(const int newScore);

	void draw(sf::RenderWindow& window); 


private: 

	void updateLevel(); 
	void reset(); 
	
	int scoreVal; 
	int level; 
	int scoreDifference = 0;
	int levelPosY = 0; 
	int scorePosY = 0; 
	int numOfDigits = 0; 
	const int difference; 


	Animation score; 
	Animation digit;  

	sf::Sprite scoreBody[10];
    // 6 positions for the level Ex. -> L123456
	sf::Sprite digitBody[6]; 
	
	float positionsOfX [10]; 
	float positionsOfXDigit[6];
};
