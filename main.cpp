#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Window\Mouse.hpp>
#include <iostream>
#include <vector>
#include "Spider.h"
#include "HealthBar.h"
#include "Bug.h"

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

	sf::Vector2f unitCircle[16]{ // each direction (up, down, left, right) has 7 options
		sf::Vector2f(1.0f, 0.0f), // 0 degrees, 0pi
		sf::Vector2f(sqrtf(3.0f) / 2.0f, 0.5f), // 30 degrees, pi/6
		sf::Vector2f(sqrtf(2.0f) / 2.0f, sqrtf(2.0f) / 2.0f), // 45 degrees, pi/4
		sf::Vector2f(0.5f, sqrtf(3.0f) / 2.0f), // 60 degrees, pi/3
		sf::Vector2f(0.0f, 1.0f), // 90 degrees, pi/2
		sf::Vector2f(-0.5f, sqrtf(3.0f) / 2.0f), // 120 degrees, 2pi/3
		sf::Vector2f(-sqrtf(2.0f) / 2.0f, sqrtf(2.0f) / 2.0f), // 135 degrees, 3pi/4
		sf::Vector2f(-sqrtf(3.0f) / 2.0f, 0.5f), // 150 degrees, 5pi/6
		sf::Vector2f(-1.0f, 0.0f), // 180 degrees, pi
		sf::Vector2f(-sqrtf(3.0f) / 2.0f, -0.5f), // 210 degrees, 7pi/6
		sf::Vector2f(-sqrtf(2.0f) / 2.0f, -sqrtf(2.0f) / 2.0f), // 225 degrees, 5pi/4
		sf::Vector2f(-0.5f, -sqrtf(3.0f) / 2.0f), // 240 degrees, 4pi/3
		sf::Vector2f(0.0f, -1.0f), // 270 degrees, 3pi/2
		sf::Vector2f(0.5f, -sqrtf(3.0f) / 2.0f), // 300 degrees, 5pi/3
		sf::Vector2f(sqrtf(2.0f) / 2.0f, -sqrtf(2.0f) / 2.0f), // 315 degrees, 7pi/4 
		sf::Vector2f(sqrtf(3.0f) / 2.0f, -0.5f), // 330 degrees, 11pi/6
	};

	size_t bugCount = 5;
	size_t bugCountMin = 5;
	sf::Texture bugTexture;
	bugTexture.loadFromFile("png/bugs.png");
	std::vector<Bug> bugVector;
	for (size_t i = 0; i < bugCount; ++i)
	{
		bugVector.push_back(Bug(&bugTexture, sf::Vector2u(4, 3), 0.0f, unitCircle));
		std::cout << bugVector.at(i);
	}

	sf::Texture spiderTexture;
	spiderTexture.loadFromFile("png/spider.png"); // orange is E25630, blue is 9fcbf8
	Spider spider(&spiderTexture, sf::Vector2u(6, 5), 0.05f);
	spider.setPosition(WINDOW_WIDTH * 34.0f / 160.0f, 
		WINDOW_HEIGHT * 12.0f / 45.0f);
	spider.setScale(widthRatio, heightRatio);

	// strand rectangles - used to determine where a bug is when its caught
	// goes from left to right
	int webStrandCount = 5;
	sf::FloatRect webStrands[5]{
		// left
		sf::FloatRect(40.0f * WINDOW_WIDTH / 160.0f,
			52.0f * WINDOW_HEIGHT / 90.0f,
			30.0f * WINDOW_WIDTH / 160.0f,
			5.0f * WINDOW_HEIGHT / 90.0f),
		// down left
		sf::FloatRect(62.0f * WINDOW_WIDTH / 160.0f,
			60.0f * WINDOW_HEIGHT / 90.0f,
			17.0f * WINDOW_WIDTH / 160.0f,
			7.0f * WINDOW_HEIGHT / 90.0f),
		// down
		sf::FloatRect(94.0f * WINDOW_WIDTH / 160.0f,
			60.0f * WINDOW_HEIGHT / 90.0f,
			7.0f * WINDOW_WIDTH / 160.0f,
			10.0f * WINDOW_HEIGHT / 90.0f),
		// down right
		sf::FloatRect(111.0f * WINDOW_WIDTH / 160.0f,
			60.0f * WINDOW_HEIGHT / 90.0f,
			22.0f * WINDOW_WIDTH / 160.0f,
			6.0f * WINDOW_HEIGHT / 90.0f),
		// right
		sf::FloatRect(125.0f * WINDOW_WIDTH / 160.0f,
			52.0f * WINDOW_HEIGHT / 90.0f,
			25.0f * WINDOW_WIDTH / 160.0f,
			3.0f * WINDOW_HEIGHT / 90.0f),
	};


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

	sf::Texture quitTexture;
	quitTexture.loadFromFile("png/quit.png");
	sf::Sprite quit;
	quit.setTexture(quitTexture);
	quit.setScale(widthRatio, heightRatio);
	quit.setPosition(3.0f * WINDOW_WIDTH / 160.0f, 80.0f * WINDOW_HEIGHT / 90.0f);

	sf::Texture retryTexture;
	retryTexture.loadFromFile("png/retry.png");
	sf::Sprite retry;
	retry.setTexture(retryTexture);
	retry.setScale(widthRatio, heightRatio);
	retry.setPosition(129.0f * WINDOW_WIDTH / 160.0f, 80.0f * WINDOW_HEIGHT / 90.0f);

	float deltaTime = 0.0f;
	sf::Clock deltaClock; // time between frames
	sf::Clock spawnClock; // time between bugs spawning
	sf::Clock healthClock; // time between health decrements

	bool inLunge = false; // spider is currently lunging
	bool delayed = false; // spider's switchTime has been extended
	bool gameIsOver = false; // health is zero
	bool caughtBug = false; // spider has caught a bug

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
					else if (!inLunge && !gameIsOver &&
						(event.key.code == sf::Keyboard::Left ||
						event.key.code == sf::Keyboard::A) &&
						spider.getRow() > 0)
					{
						spider.shift(-1);
					}
					else if (!inLunge && !gameIsOver && 
						(event.key.code == sf::Keyboard::Right ||
						event.key.code == sf::Keyboard::D) &&
						spider.getRow() < 4)
					{
						spider.shift(1);
					}
					else if (!gameIsOver && event.key.code == sf::Keyboard::Space)
					{
						inLunge = true;
						health.update(-1, deltaTime); // Fix needed: holding down space makes health continually drain
						// all bugs start fleeing when the animation starts
					}
					break;
				case sf::Event::MouseButtonPressed:
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						sf::Vector2i mousePos = sf::Mouse::getPosition(window);
						cout << "Mouseclick position: (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
						if (gameIsOver && quit.getGlobalBounds().contains(sf::Vector2f(mousePos)))
						{
							window.close();
						}
						else if (gameIsOver && retry.getGlobalBounds().contains(sf::Vector2f(mousePos)))
						{
							spawnClock.restart();
							healthClock.restart();
							health.reset(deltaTime);
							spider.resetAnimation(); // Fix needed: the spider does another quick lunge after game is reset
							bugVector.clear();
							for (size_t i = 0; i < bugCount; ++i)
							{
								bugVector.push_back(Bug(&bugTexture, sf::Vector2u(4, 3), 0.0f, unitCircle));
								std::cout << bugVector.at(i);
							}
							gameIsOver = false;
						}
					}
					break;

			}
		}

		window.clear();
		int curHealth = health.getHealth();
		
		if (curHealth <= 0)
		{
			gameIsOver = true;
		}
		else // update animations only if not game over
		{
			int bugHealth = 0; // health of prospective caught bug
			if (inLunge)
			{
				// check if any of the bugs intersect the spider sprite (all directions)
				for (size_t i = 0; i < bugCount; ++i) // check every bug
				{
					sf::FloatRect bugRect = bugVector.at(i).getGlobalBounds();
					if (delayed && webStrands[spider.getRow()].intersects(bugRect)) // bug and spider are on the same strand, spider has reached 4th frame
					{
						caughtBug = true;
						bugVector.at(i).setCaught(caughtBug);
						// bug goes into caught animation
						bugHealth = bugVector.at(i).getHealth(); // store health because it should only be incremented after spider is back in burrow
						// call destructor on bug when spider is in fifth frame
					}
				}
				if (caughtBug && spider.getCurrentImage().x == 5) // 
				{
					health.update(bugHealth, deltaTime);
					caughtBug = false;
					// increment score
				}
				inLunge = spider.lunge(deltaTime, &delayed);
			}
			if (healthClock.getElapsedTime().asSeconds() >= 20.0f) // decrement health every 20 seconds
			{
				healthClock.restart();
				health.update(-1, deltaTime);
			}
			if (spawnClock.getElapsedTime().asSeconds() >= 3.0f && bugVector.size() < bugCountMin) // spawn new bug every three seconds when they get under a certain population
			{
				spawnClock.restart();
				while (bugVector.size() < bugCountMin)
				{
					bugVector.push_back(Bug(&bugTexture, sf::Vector2u(4, 3), 0.0f, unitCircle));
					++bugCount;
				}
			}
			for (size_t i = 0; i < bugCount; ++i)
			{
				auto bugIter = bugVector.begin() + i;
				
				if (bugIter->isCaught() && spider.getCurrentImage().x == 5)
				{
					bugVector.erase(bugIter);
					--bugCount;
				}
				bugIter->update(deltaTime, unitCircle);
			}
		}

		window.draw(bgSprite);
		spider.draw(window);
		for (int i = 0; i < bugCount; ++i)
		{
			bugVector.at(i).draw(window);
		}
		if (gameIsOver) // game over
		{
			window.draw(gameOver);
			window.draw(retry);
			window.draw(quit);
		}
		health.draw(window);
		window.display();
	}

	return 0;
}