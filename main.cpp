#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "Bug.h"
#include "Spider.h"
#include "HealthBar.h"
#include "Player.h"

using std::cout;

static const unsigned int WINDOW_WIDTH = 2 * sf::VideoMode::getDesktopMode().width / 3;
static const unsigned int WINDOW_HEIGHT = 2 * sf::VideoMode::getDesktopMode().height / 3;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Trapdoor", sf::Style::Default);
	window.setVerticalSyncEnabled(true);

	sf::Texture bg;
	bg.loadFromFile("png/background.png");
	sf::Sprite bgSprite;
	bgSprite.setTexture(bg);
	unsigned int bgx = bg.getSize().x;
	unsigned int bgy = bg.getSize().y;
	float widthRatio = 1.0f * WINDOW_WIDTH / bgx;
	float heightRatio = 1.0f * WINDOW_HEIGHT / bgy;
	bgSprite.setScale(widthRatio, heightRatio);

	srand(unsigned int(time(NULL))); // initialize random int generator

	sf::Texture bugTexture;
	bugTexture.loadFromFile("png/bugs.png");

	// create a vector containing all the bugs


	sf::Vector2f unitCircle[16]{ // each direction (up, down, left, right) has 7 options
		sf::Vector2f(1.0f, 0.0f), // 0 degrees, 0pi
		sf::Vector2f(sqrtf(3.0f) / 2.0f, 0.5f), // 30 degrees, pi/6
		sf::Vector2f(sqrtf(2.0f), sqrtf(2.0f)), // 45 degrees, pi/4
		sf::Vector2f(0.5f, sqrtf(3.0f) / 2.0f), // 60 degrees, pi/3
		sf::Vector2f(0.0f, 1.0f), // 90 degrees, pi/2
		sf::Vector2f(-0.5f, sqrtf(3.0f) / 2.0f), // 120 degrees, 2pi/3
		sf::Vector2f(-sqrtf(2.0f), sqrtf(2.0f)), // 135 degrees, 3pi/4
		sf::Vector2f(-sqrtf(3.0f) / 2.0f, 0.5f), // 150 degrees, 5pi/6
		sf::Vector2f(-1.0f, 0.0f), // 180 degrees, pi
		sf::Vector2f(-sqrtf(3.0f) / 2.0f, -0.5f), // 210 degrees, 7pi/6
		sf::Vector2f(-sqrtf(2.0f), -sqrtf(2.0f)), // 225 degrees, 5pi/4
		sf::Vector2f(-0.5f, -sqrtf(3.0f) / 2.0f), // 240 degrees, 4pi/3
		sf::Vector2f(0.0f, -1.0f), // 270 degrees, 3pi/2
		sf::Vector2f(0.5f, -sqrtf(3.0f) / 2.0f), // 300 degrees, 5pi/3
		sf::Vector2f(sqrtf(2.0f), -sqrtf(2.0f)), // 315 degrees, 7pi/4 
		sf::Vector2f(sqrtf(3.0f) / 2.0f, -0.5f), // 330 degrees, 11pi/6
	};

	Player playerBug(&bugTexture, sf::Vector2u(4, 3), 0.3f, 200.0f, unitCircle);

	sf::Texture spiderTexture;
	spiderTexture.loadFromFile("png/spider.png"); // orange is E25630, blue is 9fcbf8
	Spider spider(&spiderTexture, sf::Vector2u(6, 5), 0.05f);
	spider.setPosition(WINDOW_WIDTH * 34.0f / 160.0f, WINDOW_HEIGHT * 12.0f / 45.0f);
	spider.setScale(widthRatio, heightRatio);

	sf::Texture healthTexture;
	healthTexture.loadFromFile("png/health.png");
	HealthBar health(&healthTexture, sf::Vector2u(16, 1), 20.0f);
	health.setPosition(WINDOW_WIDTH / 32.0f, WINDOW_HEIGHT / 18.0f);
	health.setScale(widthRatio, heightRatio);

	sf::Texture gameOverTexture;
	gameOverTexture.loadFromFile("png/game_over.png");
	sf::Sprite gameOver;
	gameOver.setTexture(gameOverTexture);
	gameOver.setScale(widthRatio, heightRatio);

	float deltaTime = 0.0f;
	sf::Clock deltaClock; // time between frames
	sf::Clock spawnClock; // time between bugs spawning
	sf::Clock healthClock; // time between health decrements

	bool inLunge = false; // spider is currently lunging (triggers lunge animation)
	bool delayed = false; // spider's switchTime has been extended
	bool gameIsOver = false; // health is zero

	while (window.isOpen())
	{
		deltaTime = deltaClock.restart().asSeconds();


		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:   // window closed
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape) 
					{
						window.close(); 
					}
					if ((event.key.code == sf::Keyboard::Left || 
						event.key.code == sf::Keyboard::A) &&
						spider.getRow() > 0 &&
						!inLunge && !gameIsOver)
					{
						spider.shift(-1);
					}
					if ((event.key.code == sf::Keyboard::Right ||
						event.key.code == sf::Keyboard::D) &&
						spider.getRow() < 4 &&
						!inLunge && !gameIsOver)
					{
						spider.shift(1);
					}
					if (event.key.code == sf::Keyboard::Space && !gameIsOver)
					{
						inLunge = true;
						health.update(-1, deltaTime);
					}

			}
		}

		window.clear();
		int curHealth = health.getHealth();
		
		if (curHealth >= 0) // update animations only if not game over
		{
			if (inLunge)
			{
				inLunge = spider.lunge(deltaTime, &delayed);
				// if bug is caught - health.update(bug.getHealth(), deltaTime);
				// increment score
				// else - nothing, health was already decremented
			}
			if (healthClock.getElapsedTime().asSeconds() >= 20.0f) // decrement health every 20 seconds
			{
				healthClock.restart();
				health.update(-1, deltaTime);
			}
			if (spawnClock.getElapsedTime().asSeconds() >= 3.0f) // spawn new bug every three seconds when they get under a certain population
			{
				spawnClock.restart();
				// spawn new bug
			}


			playerBug.update(deltaTime, unitCircle);
		}

		window.draw(bgSprite);
		health.draw(window);
		spider.draw(window);
		playerBug.draw(window);

		if (curHealth <= 0) // game over
		{
			window.draw(gameOver);
			gameIsOver = true;
		}

		window.display();
	}

	return 0;
}



//OBSOLETE
//Point allPoints[18]
//{
//	{10.0f * widthRatio, 50.0f * heightRatio, 'A'}, //A
//	{47.0f * widthRatio, 43.0f * heightRatio, 'B'}, //B
//	{130.0f * widthRatio, 42.0f * heightRatio, 'C'}, //C
//	{146.0f * widthRatio, 31.0f * heightRatio, 'D'}, //D
//	{39.0f * widthRatio, 65.0f * heightRatio, 'E'}, //E
//	{72.0f * widthRatio, 75.0f * heightRatio, 'F'}, //F
//	{85.0f * widthRatio, 62.0f * heightRatio, 'G'}, //G
//	{115.0f * widthRatio, 65.0f * heightRatio, 'H'}, //H
//	{137.0f * widthRatio, 60.0f * heightRatio, 'I'}, //I
//	{30.0f * widthRatio, 78.0f * heightRatio, 'J'}, //J
//	{145.0f * widthRatio, 76.0f * heightRatio, 'K'}, //K
//	{-20.0f * widthRatio, 45.0f * heightRatio, '1'}, //S1
//	{26.0f * widthRatio, 110.0f * heightRatio, '2'}, //S2
//	{51.0f * widthRatio, 110.0f * heightRatio, '3'}, //S3
//	{95.0f * widthRatio, 110.0f * heightRatio, '4'}, //S4
//	{135.0f * widthRatio, 110.0f * heightRatio, '5'}, //S5
//	{180.0f * widthRatio, 70.0f * heightRatio, '6'}, //S6
//	{180.0f * widthRatio, 42.0f * heightRatio, '7'} //S7
//};
//
////path connections
//allPoints[0].connect(allPoints[1]);
//allPoints[0].connect(allPoints[4]);
//allPoints[0].connect(allPoints[9]);
//allPoints[0].connect(allPoints[11]);
//
//allPoints[1].connect(allPoints[0]);
//allPoints[1].connect(allPoints[4]);
//allPoints[1].connect(allPoints[5]);
//allPoints[1].connect(allPoints[6]);
//allPoints[1].connect(allPoints[11]);
//
//allPoints[2].connect(allPoints[3]);
//allPoints[2].connect(allPoints[7]);
//allPoints[2].connect(allPoints[8]);
//allPoints[2].connect(allPoints[16]);
//
//allPoints[3].connect(allPoints[2]);
//allPoints[3].connect(allPoints[8]);
//allPoints[3].connect(allPoints[10]);
//allPoints[3].connect(allPoints[17]);
//
//allPoints[4].connect(allPoints[0]);
//allPoints[4].connect(allPoints[1]);
//allPoints[4].connect(allPoints[5]);
//allPoints[4].connect(allPoints[9]);
//allPoints[4].connect(allPoints[12]);
//
//allPoints[5].connect(allPoints[1]);
//allPoints[5].connect(allPoints[4]);
//allPoints[5].connect(allPoints[6]);
//allPoints[5].connect(allPoints[9]);
//allPoints[5].connect(allPoints[13]);
//
//allPoints[6].connect(allPoints[1]);
//allPoints[6].connect(allPoints[5]);
//allPoints[6].connect(allPoints[7]);
//allPoints[6].connect(allPoints[14]);
//
//allPoints[7].connect(allPoints[6]);
//allPoints[7].connect(allPoints[2]);
//allPoints[7].connect(allPoints[8]);
//allPoints[7].connect(allPoints[14]);
//
//allPoints[8].connect(allPoints[2]);
//allPoints[8].connect(allPoints[7]);
//allPoints[8].connect(allPoints[3]);
//allPoints[8].connect(allPoints[10]);
//allPoints[8].connect(allPoints[15]);
//
//allPoints[9].connect(allPoints[0]);
//allPoints[9].connect(allPoints[4]);
//allPoints[9].connect(allPoints[5]);
//allPoints[9].connect(allPoints[13]);
//
//allPoints[10].connect(allPoints[3]);
//allPoints[10].connect(allPoints[8]);
//allPoints[10].connect(allPoints[15]);
//
//allPoints[11].connect(allPoints[0]);
//allPoints[11].connect(allPoints[1]);
//
//allPoints[12].connect(allPoints[4]);
//
//allPoints[13].connect(allPoints[9]);
//allPoints[13].connect(allPoints[5]);
//
//allPoints[14].connect(allPoints[6]);
//allPoints[14].connect(allPoints[7]);
//
//allPoints[15].connect(allPoints[8]);
//allPoints[15].connect(allPoints[10]);
//
//allPoints[16].connect(allPoints[2]);
//
//allPoints[17].connect(allPoints[3]);
//
//// edges within range: B to E, B to F, B to G, G to F, G to S4, G to H,
//// H to C, H to S4, H to I, H to S5, D to I


//Bug bug0(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
//Bug bug1(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
//Bug bug2(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
//Bug bug3(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
//Bug bug4(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
//
//// Failed paths
//std::list<const Point*> failPath0 = { &allPoints[11], &allPoints[1] }; // S1 to B
//std::list<const Point*> failPath1 = { &allPoints[12], &allPoints[4] }; // S2 to E
//std::list<const Point*> failPath2 = { &allPoints[13], &allPoints[5] }; // S3 to F
//std::list<const Point*> failPath3 = { &allPoints[14], &allPoints[7] }; // S4 to H
//std::list<const Point*> failPath4 = { &allPoints[15], &allPoints[9] }; // S5 to I
//std::list<const Point*> failPath5 = { &allPoints[15], &allPoints[10] }; // S5 to K