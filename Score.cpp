#include <cmath>
#include "Score.h"
#include <iostream>
#include "Animation.h"


using namespace std;

Score::Score(sf::Texture* textureScore, sf::Vector2u imageCountScore, sf::Texture* textureDigit,
	sf::Vector2u imageCountDigit, const int bgWidth, sf::Vector2f bgPosition, const int lvWidth, sf::Vector2f lvPosition, const int difference)
	:scoreVal(0), level(1), levelPosY(lvPosition.y), scorePosY(bgPosition.y),
	score(textureScore, imageCountScore), digit(textureDigit, imageCountDigit), difference(difference)
{
	score.updateManually(0, 0);


	for (int i = 0; i < 10; ++i)
	{
		//Setting positionsOfX Array
		int oneFrame = bgWidth / 10;
		positionsOfX[i] = ((bgPosition.x + bgWidth - (oneFrame / 4)) - (oneFrame * (i + 1)));

		//Setting scoreBody Array
		scoreBody[i].setTexture(*textureScore);
		scoreBody[i].setScale(5.0f, 5.0f);
		scoreBody[i].setTextureRect(score.uvRect);
		scoreBody[i].setPosition(positionsOfX[i], scorePosY);
	}

	for (int i = 0; i < 6; ++i)
	{
		int oneFrame = lvWidth / 7; // 6 digits + the "L" = 7
		positionsOfXDigit[i] = ((lvPosition.x) + (oneFrame * (i + 1)));

		digitBody[i].setTexture(*textureDigit);
		digitBody[i].setScale(5.0f, 5.0f);
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
	return scoreVal;
}

int Score::getLevel() const
{
	return level;
}

void Score::updateScore(const int newScore)
{
	int position = 0;
	scoreVal += newScore;
	int newScoreNum = scoreVal;

	scoreDifference += newScore;
	//1
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

		scoreBody[position].setTextureRect(score.uvRect);
		scoreBody[position].setPosition(positionsOfX[position], scorePosY);

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
	numOfDigits = 0;

	while (divisor != 0) //newLvlNum
	{
		int firstDigit = newLevel / divisor;
		newLevel = newLevel % divisor;
		divisor /= 10;

		digit.updateManually(0, firstDigit);

		digitBody[position].setTextureRect(digit.uvRect);
		digitBody[position].setPosition(positionsOfXDigit[position], levelPosY);

		++numOfDigits;
		++position;
	}
	cout << "numOfDigits: " << numOfDigits << endl;
}

void Score::reset()
{
	level = 1;
	numOfDigits = 1;
	digit.updateManually(0, level);
	digitBody[0].setTextureRect(digit.uvRect);
	digitBody[0].setPosition(positionsOfXDigit[0], levelPosY);
}

void Score::draw(sf::RenderWindow& window)
{
	//Draws the score 
	for (int i = 0; i < 10; ++i)
	{
		window.draw(scoreBody[i]);
	}

	//Draws the levels
	for (int i = 0; i < numOfDigits; ++i)
	{
		window.draw(digitBody[i]);
	}
}