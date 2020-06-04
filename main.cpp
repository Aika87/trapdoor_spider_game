#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "Bug.h"
#include "Spider.h"

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

	Point allPoints[18]
	{
		{10.0f * widthRatio, 50.0f * heightRatio, 'A'}, //A
		{47.0f * widthRatio, 43.0f * heightRatio, 'B'}, //B
		{130.0f * widthRatio, 42.0f * heightRatio, 'C'}, //C
		{146.0f * widthRatio, 31.0f * heightRatio, 'D'}, //D
		{39.0f * widthRatio, 65.0f * heightRatio, 'E'}, //E
		{72.0f * widthRatio, 75.0f * heightRatio, 'F'}, //F
		{85.0f * widthRatio, 62.0f * heightRatio, 'G'}, //G
		{115.0f * widthRatio, 65.0f * heightRatio, 'H'}, //H
		{137.0f * widthRatio, 60.0f * heightRatio, 'I'}, //I
		{30.0f * widthRatio, 78.0f * heightRatio, 'J'}, //J
		{145.0f * widthRatio, 76.0f * heightRatio, 'K'}, //K
		{-20.0f * widthRatio, 45.0f * heightRatio, '1'}, //S1
		{26.0f * widthRatio, 110.0f * heightRatio, '2'}, //S2
		{51.0f * widthRatio, 110.0f * heightRatio, '3'}, //S3
		{95.0f * widthRatio, 110.0f * heightRatio, '4'}, //S4
		{135.0f * widthRatio, 110.0f * heightRatio, '5'}, //S5
		{180.0f * widthRatio, 70.0f * heightRatio, '6'}, //S6
		{180.0f * widthRatio, 42.0f * heightRatio, '7'} //S7
	};

	//path connections
	allPoints[0].connect(allPoints[1]);
	allPoints[0].connect(allPoints[4]);
	allPoints[0].connect(allPoints[9]);
	allPoints[0].connect(allPoints[11]);

	allPoints[1].connect(allPoints[0]);
	allPoints[1].connect(allPoints[4]);
	allPoints[1].connect(allPoints[5]);
	allPoints[1].connect(allPoints[6]);
	allPoints[1].connect(allPoints[11]);

	allPoints[2].connect(allPoints[3]);
	allPoints[2].connect(allPoints[7]);
	allPoints[2].connect(allPoints[8]);
	allPoints[2].connect(allPoints[16]);

	allPoints[3].connect(allPoints[2]);
	allPoints[3].connect(allPoints[8]);
	allPoints[3].connect(allPoints[10]);
	allPoints[3].connect(allPoints[17]);

	allPoints[4].connect(allPoints[0]);
	allPoints[4].connect(allPoints[1]);
	allPoints[4].connect(allPoints[5]);
	allPoints[4].connect(allPoints[9]);
	allPoints[4].connect(allPoints[12]);

	allPoints[5].connect(allPoints[1]);
	allPoints[5].connect(allPoints[4]);
	allPoints[5].connect(allPoints[6]);
	allPoints[5].connect(allPoints[9]);
	allPoints[5].connect(allPoints[13]);

	allPoints[6].connect(allPoints[1]);
	allPoints[6].connect(allPoints[5]);
	allPoints[6].connect(allPoints[7]);
	allPoints[6].connect(allPoints[14]);

	allPoints[7].connect(allPoints[6]);
	allPoints[7].connect(allPoints[2]);
	allPoints[7].connect(allPoints[8]);
	allPoints[7].connect(allPoints[14]);

	allPoints[8].connect(allPoints[2]);
	allPoints[8].connect(allPoints[7]);
	allPoints[8].connect(allPoints[3]);
	allPoints[8].connect(allPoints[10]);
	allPoints[8].connect(allPoints[15]);

	allPoints[9].connect(allPoints[0]);
	allPoints[9].connect(allPoints[4]);
	allPoints[9].connect(allPoints[5]);
	allPoints[9].connect(allPoints[13]);

	allPoints[10].connect(allPoints[3]);
	allPoints[10].connect(allPoints[8]);
	allPoints[10].connect(allPoints[15]);

	allPoints[11].connect(allPoints[0]);
	allPoints[11].connect(allPoints[1]);

	allPoints[12].connect(allPoints[4]);

	allPoints[13].connect(allPoints[9]);
	allPoints[13].connect(allPoints[5]);

	allPoints[14].connect(allPoints[6]);
	allPoints[14].connect(allPoints[7]);

	allPoints[15].connect(allPoints[8]);
	allPoints[15].connect(allPoints[10]);

	allPoints[16].connect(allPoints[2]);

	allPoints[17].connect(allPoints[3]);

	// edges within range: B to E, B to F, B to G, G to F, G to S4, G to H,
	// H to C, H to S4, H to I, H to S5, D to I

	sf::Texture bugTexture;
	bugTexture.loadFromFile("png/bugs.png");

	// create a vector containing all the 

	Bug bug0(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
	Bug bug1(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
	Bug bug2(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
	Bug bug3(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
	Bug bug4(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);

	// Failed paths
	std::list<const Point*> failPath0 = { &allPoints[11], &allPoints[1] }; // S1 to B
	std::list<const Point*> failPath1 = { &allPoints[12], &allPoints[4] }; // S2 to E
	std::list<const Point*> failPath2 = { &allPoints[13], &allPoints[5] }; // S3 to F
	std::list<const Point*> failPath3 = { &allPoints[14], &allPoints[7] }; // S4 to H
	std::list<const Point*> failPath4 = { &allPoints[15], &allPoints[9] }; // S5 to I
	std::list<const Point*> failPath5 = { &allPoints[15], &allPoints[10] }; // S5 to K

	std::cout << bug0;

	sf::Texture spiderTexture;
	spiderTexture.loadFromFile("png/spider.png");
	Spider spider(&spiderTexture, sf::Vector2u(6, 5), 0.05f);
	spider.setPosition(WINDOW_WIDTH * 9.0f / 40.0f, WINDOW_HEIGHT * 12.0f / 45.0f);
	spider.setScale(widthRatio, heightRatio);

	float deltaTime = 0.0f;
	sf::Clock deltaClock; // time between frames
	sf::Clock spawnClock; // time between bugs spawning
	sf::Clock healthClock; // time between health decrements

	bool inLunge = false; // whether or not the spider is lunging
	bool delayed = false; // whether or not the spider's switch time is delayed (making retraction slower)

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
						!inLunge)
					{
						spider.shift(-1);
					}
					if ((event.key.code == sf::Keyboard::Right ||
						event.key.code == sf::Keyboard::D) &&
						spider.getRow() < 4 &&
						!inLunge)
					{
						spider.shift(1);
					}
					if (event.key.code == sf::Keyboard::Space)
					{
						inLunge = true;
					}

			}
		}

		window.clear();
		
		
		if (inLunge)
		{ 
			inLunge = spider.lunge(deltaTime, &delayed);
			// decrement health here 
			// check if bug is caught
		}

		if (healthClock.getElapsedTime().asSeconds() >= 20.0f) // decrement health every 20 seconds
		{
			healthClock.restart();
			//decrement health here
		}

		if (spawnClock.getElapsedTime().asSeconds() >= 3.0f) // spawn new bug every three seconds when they get under a certain population
		{
			spawnClock.restart();
			// spawn new bug
		}

		bug0.update(allPoints, deltaTime);
		bug1.update(allPoints, deltaTime);
		bug2.update(allPoints, deltaTime);
		bug3.update(allPoints, deltaTime);
		bug4.update(allPoints, deltaTime);

		window.draw(bgSprite);

		// Place red dot at each point
		sf::RectangleShape rect(sf::Vector2f(5.0f, 5.0f));
		rect.setFillColor(sf::Color::Red);
		for (int i = 0; i < 18; ++i)
		{
			rect.setPosition(allPoints[i].getPosition());
			window.draw(rect);
		}

		spider.draw(window);
		bug0.draw(window);


		window.display();
	}

	return 0;
}
