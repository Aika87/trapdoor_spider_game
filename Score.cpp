#include <cmath>
#include "Score.h"
#include <iostream>
#include "Animation.h"


using namespace std; 

Score::Score(sf::Texture* textureScore, sf::Vector2u imageCountScore, sf::Texture* textureDigit, 
	sf::Vector2u imageCountDigit, const int bgWidth, sf::Vector2f bgPosition, const int lvWidth, sf::Vector2f lvPosition)
	:scoreVal(0), level(1), levelPosY(lvPosition.y), scorePosY(bgPosition.y), 
	score(textureScore, imageCountScore), digit(textureDigit, imageCountDigit)
{
	
	scoreBody0.setTexture(*textureScore);
	scoreBody0.setScale(5.0f, 5.0f);

	scoreBody1.setTexture(*textureScore);
	scoreBody1.setScale(5.0f, 5.0f);

	scoreBody2.setTexture(*textureScore);
	scoreBody2.setScale(5.0f, 5.0f);

	scoreBody3.setTexture(*textureScore);
	scoreBody3.setScale(5.0f, 5.0f);

	scoreBody4.setTexture(*textureScore);
	scoreBody4.setScale(5.0f, 5.0f);

	scoreBody5.setTexture(*textureScore);
	scoreBody5.setScale(5.0f, 5.0f);

	scoreBody6.setTexture(*textureScore);
	scoreBody6.setScale(5.0f, 5.0f);

	scoreBody7.setTexture(*textureScore);
	scoreBody7.setScale(5.0f, 5.0f);

	scoreBody8.setTexture(*textureScore);
	scoreBody8.setScale(5.0f, 5.0f);

	scoreBody9.setTexture(*textureScore);
	scoreBody9.setScale(5.0f, 5.0f);
	
	digitBody0.setTexture(*textureDigit);
	digitBody0.setScale(5.0f, 5.0f);

	digitBody1.setTexture(*textureDigit);
	digitBody1.setScale(5.0f, 5.0f);

	digitBody2.setTexture(*textureDigit);
	digitBody2.setScale(5.0f, 5.0f);

	digitBody3.setTexture(*textureDigit);
	digitBody3.setScale(5.0f, 5.0f);

	digitBody4.setTexture(*textureDigit);
	digitBody4.setScale(5.0f, 5.0f);

	digitBody5.setTexture(*textureDigit);
	digitBody5.setScale(5.0f, 5.0f);
	

	for (int i = 0; i < 10; ++i)
	{
		int oneFrame = bgWidth / 10; 
		
		positionsOfX[i] = ((bgPosition.x + bgWidth - (oneFrame /4)) - (oneFrame * (i + 1)));
	}

	score.updateManually(0, 0);
	scoreBody0.setTextureRect(score.uvRect);
	scoreBody1.setTextureRect(score.uvRect);
	scoreBody2.setTextureRect(score.uvRect);
	scoreBody3.setTextureRect(score.uvRect);
	scoreBody4.setTextureRect(score.uvRect);
	scoreBody5.setTextureRect(score.uvRect);
	scoreBody6.setTextureRect(score.uvRect);
	scoreBody7.setTextureRect(score.uvRect);
	scoreBody8.setTextureRect(score.uvRect);
	scoreBody9.setTextureRect(score.uvRect);

	scoreBody0.setPosition(positionsOfX[0], scorePosY); 
	scoreBody1.setPosition(positionsOfX[1], scorePosY);
	scoreBody2.setPosition(positionsOfX[2], scorePosY);
	scoreBody3.setPosition(positionsOfX[3], scorePosY);
	scoreBody4.setPosition(positionsOfX[4], scorePosY);
	scoreBody5.setPosition(positionsOfX[5], scorePosY);
	scoreBody6.setPosition(positionsOfX[6], scorePosY);
	scoreBody7.setPosition(positionsOfX[7], scorePosY);
	scoreBody8.setPosition(positionsOfX[8], scorePosY);
	scoreBody9.setPosition(positionsOfX[9], scorePosY);


	for (int i = 0; i < 6; ++i)
	{
		int oneFrame = lvWidth / 7; // 6 digits + the "L" = 7

		positionsOfXDigit[i] = ((lvPosition.x) + (oneFrame * (i + 1)));
	}

	reset(); 

}

Score::~Score() {}

void Score::setScore(int newScore)
{
	scoreVal = newScore;
}

void Score::setLevel(int newLevel)
{
	level = newLevel;
}

int Score::getScore() const
{
	return 0; 
}

int Score::getLevel() const
{
	return 0; 
}

void Score::updateScore(const int newScore, const int difference)
{
	int position = 0; 
	scoreVal += newScore; 
	int newScoreNum = scoreVal;

	scoreDifference += newScore;

	while (newScoreNum != 0)
	{
		int digitNum = newScoreNum % 10; 

		if (newScore == 0)
		{
			digitNum = 0; 
			scoreVal = 0; 
			reset(); 
		}

		newScoreNum /= 10; 
		score.updateManually(0, digitNum);

		//switch 
		switch (position)
		{
		case 0:
			scoreBody0.setTextureRect(score.uvRect);
			scoreBody0.setPosition(positionsOfX[position], scorePosY);
			break; 
		case 1:
			scoreBody1.setTextureRect(score.uvRect);
			scoreBody1.setPosition(positionsOfX[position], scorePosY);
			break;
		case 2:
			scoreBody2.setTextureRect(score.uvRect);
			scoreBody2.setPosition(positionsOfX[position], scorePosY);
			break;
		case 3:
			scoreBody3.setTextureRect(score.uvRect);
			scoreBody3.setPosition(positionsOfX[position], scorePosY);
			break;
		case 4: 
			scoreBody4.setTextureRect(score.uvRect);
			scoreBody4.setPosition(positionsOfX[position], scorePosY);
			break;
		case 5:
			scoreBody5.setTextureRect(score.uvRect);
			scoreBody5.setPosition(positionsOfX[position], scorePosY);
			break;
		case 6:
			scoreBody6.setTextureRect(score.uvRect);
			scoreBody6.setPosition(positionsOfX[position], scorePosY);
			break;
		case 7:
			scoreBody7.setTextureRect(score.uvRect);
			scoreBody7.setPosition(positionsOfX[position], scorePosY);
			break;
		case 8:
			scoreBody8.setTextureRect(score.uvRect);
			scoreBody8.setPosition(positionsOfX[position], scorePosY);
			break;
		case 9:
			scoreBody9.setTextureRect(score.uvRect);
			scoreBody9.setPosition(positionsOfX[position], scorePosY);
			break;
		} 

		++position; 

		if (scoreDifference >= difference)
		{
			updateLevel(); 
		}
	}
}

void Score::updateLevel()
{
	scoreDifference = 0;
	level++;

	int position = 0;
	int newLevel = level;

	// Finding the number of digits
	int levelLength = 0;

	while (newLevel != 0)
	{
		newLevel /= 10;
		++levelLength;
	}

	int divisor = pow(10, (levelLength - 1));

	newLevel = level;

	/*if (updatedLevel == 0)
	{
		newLevel = 1;
	}*/

	while (divisor != 0) //newLvlNum
	{
		int firstDigit = newLevel / divisor;
		newLevel = newLevel % divisor;

		divisor /= 10;

		digit.updateManually(0, firstDigit);

		//switch 
		switch (position)
		{
		case 0:
			digitBody0.setTextureRect(digit.uvRect);
			digitBody0.setPosition(positionsOfXDigit[position], levelPosY);
			break;
		case 1:
			digitBody1.setTextureRect(digit.uvRect);
			digitBody1.setPosition(positionsOfXDigit[position], levelPosY);
			break;
		case 2:
			digitBody2.setTextureRect(digit.uvRect);
			digitBody2.setPosition(positionsOfXDigit[position], levelPosY);
			break;
		case 3:
			digitBody3.setTextureRect(digit.uvRect);
			digitBody3.setPosition(positionsOfXDigit[position], levelPosY);
			break;
		case 4:
			digitBody4.setTextureRect(digit.uvRect);
			digitBody4.setPosition(positionsOfXDigit[position], levelPosY);
			break;
		case 5:
			digitBody5.setTextureRect(digit.uvRect);
			digitBody5.setPosition(positionsOfXDigit[position], levelPosY);
			break;
		}

		++position;
	}
}

void Score::reset()
{
	level = 1;
	
	digit.updateManually(0, level);
	digitBody0.setTextureRect(digit.uvRect);

	/*digit.updateManually(0, 0);
	digitBody1.setTextureRect(digit.uvRect);
	digitBody2.setTextureRect(digit.uvRect);
	digitBody3.setTextureRect(digit.uvRect);
	digitBody4.setTextureRect(digit.uvRect);
	digitBody5.setTextureRect(digit.uvRect);*/

	digitBody0.setPosition(positionsOfXDigit[0], levelPosY);

	// Something is wrong with these because if the position isn't set off the screen it shows up in the upper left hand corner
	digitBody1.setPosition(1000, 1000);
	digitBody2.setPosition(1000, 1000);
	digitBody3.setPosition(1000, 1000);
	digitBody4.setPosition(1000, 1000);
	digitBody5.setPosition(1000, 1000); 
}

void Score::draw(sf::RenderWindow& window)
{
	window.draw(scoreBody0);
	window.draw(scoreBody1);
	window.draw(scoreBody2);
	window.draw(scoreBody3);
	window.draw(scoreBody4);
	window.draw(scoreBody5);
	window.draw(scoreBody6);
	window.draw(scoreBody7);
	window.draw(scoreBody8);
	window.draw(scoreBody9);

	window.draw(digitBody0);
	window.draw(digitBody1);
	window.draw(digitBody2);
	window.draw(digitBody3);
	window.draw(digitBody4);
	window.draw(digitBody5);
}