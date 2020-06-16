#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Window\Mouse.hpp>
#include <iostream>
#include <vector>
#include "Spider.h"
#include "HealthBar.h"
#include "Bug.h"
#include "Score.h"
#include "AnimatedButton.h"

using std::cout;
using std::endl;

static const unsigned int WINDOW_WIDTH = 2 * sf::VideoMode::getDesktopMode().width / 3;
static const unsigned int WINDOW_HEIGHT = 2 * sf::VideoMode::getDesktopMode().height / 3;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Trapdoor", sf::Style::Default);
	window.setVerticalSyncEnabled(true);


	srand(unsigned int(time(NULL)));
	enum state {TITLE, IN_GAME, GAME_OVER};

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

sf::Texture bg;
	bg.loadFromFile("png/background.png");
	sf::Sprite bgSprite;
	bgSprite.setTexture(bg);
	unsigned int bgx = bg.getSize().x;
	unsigned int bgy = bg.getSize().y;
	float widthRatio = 1.0f * WINDOW_WIDTH / bgx;
	float heightRatio = 1.0f * WINDOW_HEIGHT / bgy;
	bgSprite.setScale(widthRatio, heightRatio);

	sf::Texture titleTexture;
	titleTexture.loadFromFile("png/title_screen.png");
	sf::Sprite title;
	title.setTexture(titleTexture);
	title.setScale(widthRatio, heightRatio);

	sf::Texture startTexture;
	startTexture.loadFromFile("png/start_button.png");
	AnimatedButton start(&startTexture, sf::Vector2u(2, 1), 1.0f);
	start.setPosition(61.0f * WINDOW_WIDTH / 160.0f, 45.0f * WINDOW_HEIGHT / 90.0f);
	start.setScale(widthRatio, heightRatio);

	sf::Texture bugTexture;
	bugTexture.loadFromFile("png/bugs.png");
	AnimatedButton titleBugs(&bugTexture, sf::Vector2u(4, 1), 0.5f);
	titleBugs.setPosition(115.0f * WINDOW_WIDTH / 160.0f, 42.0f * WINDOW_HEIGHT / 90.0f);
	titleBugs.setScale(widthRatio, heightRatio);

	size_t bugCount = 5;
	size_t bugCountMin = 5;
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
	retry.setPosition(121.0f * WINDOW_WIDTH / 160.0f, 80.0f * WINDOW_HEIGHT / 90.0f);

	sf::Texture scoreBgTexture;
	scoreBgTexture.loadFromFile("png/scoreBg.png");
	sf::Sprite scoreBg;
	scoreBg.setTexture(scoreBgTexture);
	scoreBg.setScale(5.0f, 5.0f);
	scoreBg.setPosition(WINDOW_WIDTH - scoreBg.getGlobalBounds().width - 20, WINDOW_HEIGHT / 18.0f);

	sf::Texture levelTexture;
	levelTexture.loadFromFile("png/level.png");
	sf::Sprite level;
	level.setTexture(levelTexture);
	level.setScale(5.0f, 5.0f);
	level.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 18.0f);

	sf::Texture scoreTexture;
	scoreTexture.loadFromFile("png/score.png");
	sf::Texture digitTexture;
	digitTexture.loadFromFile("png/digits.png");
	Score score(&scoreTexture, sf::Vector2u(10, 1), &digitTexture, sf::Vector2u(10, 1),
		scoreBg.getGlobalBounds().width, scoreBg.getPosition(), level.getGlobalBounds().width, level.getPosition(), 2000);

	float deltaTime = 0.0f;
	sf::Clock deltaClock; // time between frames
	sf::Clock healthClock; // time between health decrements

	bool inLunge = false; // spider is currently lunging
	bool delayed = false; // spider's switchTime has been extended
	bool caughtBug = false; // spider has caught a bug
	state gameState = TITLE;

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
					switch (gameState)
					{
					case TITLE:
						if (event.key.code == sf::Keyboard::Return)
						{
							gameState = IN_GAME;
						}
						break;
					case IN_GAME:
						if (!inLunge &&
							(event.key.code == sf::Keyboard::Left ||
							event.key.code == sf::Keyboard::A) &&
							spider.getRow() > 0)
							{
							spider.shift(-1);
							}
						else if (!inLunge && 
							(event.key.code == sf::Keyboard::Right ||
							event.key.code == sf::Keyboard::D) &&
							spider.getRow() < 4)
						{
							spider.shift(1);
						}
						else if (event.key.code == sf::Keyboard::Space)
						{
							inLunge = true;
						}
						break;
					case GAME_OVER:
						if (event.key.code == sf::Keyboard::Q)
						{
							window.close();
						}
						else if (event.key.code == sf::Keyboard::R)
						{
							gameState = IN_GAME;
							healthClock.restart();
							health.reset(deltaTime);
							score.updateScore(0);
							spider.resetAnimation(); // Fix needed: the spider does another quick lunge after game is reset
							bugVector.clear();
							for (size_t i = 0; i < bugCount; ++i)
							{
								bugVector.push_back(Bug(&bugTexture, sf::Vector2u(4, 3), 0.0f, unitCircle));
								std::cout << bugVector.at(i);
							}
						}
						break;
					default:
						cout << "Game state error." << endl;
						break;
					}
					break;
				case sf::Event::KeyReleased:
					if (gameState == IN_GAME && event.key.code == sf::Keyboard::Space)
					{
						health.update(-1, deltaTime);
						cout << "Used energy for lunge. Health = " << health.getHealth() << endl;
					}
					break;

			}
		}

		window.clear();
		int curHealth = health.getHealth();

		switch (gameState) 
		{
		case TITLE:
			start.update(deltaTime);
			titleBugs.update(deltaTime);
			window.draw(title);
			start.draw(window);
			titleBugs.draw(window);
			break;
		case IN_GAME:
			if (curHealth <= 0)
			{
				gameState = GAME_OVER;
			}
			else 
			{
				if (inLunge)
				{
					unsigned int spiderRow = spider.getRow();
					// check if any of the bugs intersect the spider sprite (all directions)
					for (size_t i = 0; i < bugCount; ++i) // check every bug
					{
						sf::FloatRect bugRect = bugVector.at(i).getGlobalBounds();
						if (delayed && webStrands[spiderRow].intersects(bugRect)) // bug and spider are on the same strand, spider has reached 4th frame
						{
							caughtBug = true;
							bugVector.at(i).setCaught(caughtBug);
						}
						else if (!webStrands[spiderRow].intersects(bugRect))
						{
							bugVector.at(i).flee();
						}
					}
					if (caughtBug && spider.getCurrentImage().x == 5)
					{
						healthClock.restart();
						caughtBug = false;
					}
					inLunge = spider.lunge(deltaTime, &delayed);
				}
				if (healthClock.getElapsedTime().asSeconds() >= 20.0f) // decrement health every 20 seconds
				{
					healthClock.restart();
					health.update(-1, deltaTime);
					cout << "Getting hungry. Health = " << health.getHealth() << endl;
				}
				if (!inLunge && bugCount < bugCountMin) // spawn new bug every three seconds when they get under a certain population
				{
					while (bugVector.size() < bugCountMin)
					{
						bugVector.push_back(Bug(&bugTexture, sf::Vector2u(4, 3), 0.0f, unitCircle));
						++bugCount;
					}
				}
				for (size_t i = 0; i < bugCount; ++i)
				{
					auto bugIter = bugVector.begin() + i;
					sf::FloatRect bugRect = bugIter->getGlobalBounds();
					if (bugIter->isCaught() && spider.getCurrentImage().x == 5)
					{
						int bugHealth = bugIter->getHealth();
						health.update(bugHealth, deltaTime);
						score.updateScore(bugHealth);
						cout << "Bug caught, worth " << bugHealth << " health. New health = " << health.getHealth() << endl;
						cout << "Score = " << score.getScore() << endl;
						bugVector.erase(bugIter);
						--bugCount;
					}
					else if (bugIter->isFleeing() && (bugRect.top > WINDOW_HEIGHT ||
						bugRect.left > WINDOW_WIDTH || bugRect.left + bugRect.width < 0.0f))
					{
						bugVector.erase(bugIter);
						--bugCount;
					}
					bugIter->update(deltaTime, unitCircle);
				}
			}
			window.draw(bgSprite);
			spider.draw(window);
			for (Bug b : bugVector)
			{
				b.draw(window);
			}
			window.draw(level);
			window.draw(scoreBg);
			score.draw(window);
			health.draw(window);
			break;
		case GAME_OVER:
			window.draw(bgSprite);
			spider.draw(window);
			for (Bug b : bugVector)
			{
				b.draw(window);
			}
			window.draw(gameOver);
			window.draw(retry);
			window.draw(quit);
			window.draw(level);
			window.draw(scoreBg);
			score.draw(window);
			health.draw(window);
			break;
		default:
			cout << "Game state error." << endl;
			break;
		}
		window.display();
	}

	return 0;
}
