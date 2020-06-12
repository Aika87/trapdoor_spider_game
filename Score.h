#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"

class Score
{
public:

	Score(sf::Texture* textureScore, sf::Vector2u imageCountScore, sf::Texture* textureLevel, sf::Vector2u imageCountLevel,
		const int bgWidth, sf::Vector2f bgPosition, const int lvWidth, sf::Vector2f lvPosition);
	~Score(); 
	
	void setScore(int newScore); 
	void setLevel(int newLevel); 

	int getScore() const; 
	int getLevel() const; 
	
	void updateScore(const int newScore, const int difference);

	void draw(sf::RenderWindow& window); 


private: 

	void updateLevel(); 
	void reset(); 
	
	int scoreVal; 
	int level; 
	int scoreDifference = 0;
	int levelPosY = 0; 
	int scorePosY = 0; 


	Animation score; 
	Animation digit;  

	sf::Sprite scoreBody0;
	sf::Sprite scoreBody1; 
	sf::Sprite scoreBody2; 
	sf::Sprite scoreBody3;
	sf::Sprite scoreBody4;
	sf::Sprite scoreBody5; 
	sf::Sprite scoreBody6; 
	sf::Sprite scoreBody7;
	sf::Sprite scoreBody8; 
	sf::Sprite scoreBody9; 

    // 6 positions for the level Ex. -> L123456
	sf::Sprite digitBody0;
	sf::Sprite digitBody1;
	sf::Sprite digitBody2;
	sf::Sprite digitBody3;
	sf::Sprite digitBody4;
	sf::Sprite digitBody5;
	

	float positionsOfX [10]; 

	float positionsOfXDigit[6];
};
