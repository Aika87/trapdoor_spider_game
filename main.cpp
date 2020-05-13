#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
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
	bgSprite.setScale(1.0f * widthRatio, 1.0f * heightRatio);

	srand(unsigned int(time(NULL))); // initialize random int generator

	Point allPoints[18]
	{
		{10.0f * widthRatio, 50.0f * heightRatio}, //A
		{47.0f * widthRatio, 43.0f * heightRatio}, //B
		{130.0f * widthRatio, 42.0f * heightRatio}, //C
		{146.0f * widthRatio, 31.0f * heightRatio}, //D
		{39.0f * widthRatio, 65.0f * heightRatio}, //E
		{72.0f * widthRatio, 75.0f * heightRatio}, //F
		{85.0f * widthRatio, 62.0f * heightRatio}, //G
		{115.0f * widthRatio, 65.0f * heightRatio}, //H
		{137.0f * widthRatio, 60.0f * heightRatio}, //I
		{30.0f * widthRatio, 78.0f * heightRatio}, //J
		{145.0f * widthRatio, 76.0f * heightRatio}, //K
		{-20.0f * widthRatio, 45.0f * heightRatio}, //S1
		{26.0f * widthRatio, 110.0f * heightRatio}, //S2
		{51.0f * widthRatio, 110.0f * heightRatio}, //S3
		{95.0f * widthRatio, 110.0f * heightRatio}, //S4
		{135.0f * widthRatio, 110.0f * heightRatio}, //S5
		{180.0f * widthRatio, 70.0f * heightRatio}, //S6
		{180.0f * widthRatio, 42.0f * heightRatio} //S7
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
	allPoints[1].connect(allPoints[2]);
	allPoints[1].connect(allPoints[11]);

	allPoints[2].connect(allPoints[1]);
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

	Bug bug0(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
	Bug bug1(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
	Bug bug2(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
	std::cout << bug0 << bug1 << bug2;

	float deltaTime = 0.0f;
	sf::Clock deltaClock;
	sf::Clock spawnClock;

	bool inLunge = false;

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
						!inLunge)
					{
						inLunge = true;
					}
					if ((event.key.code == sf::Keyboard::Left ||
						event.key.code == sf::Keyboard::A) &&
						(event.key.code == sf::Keyboard::Down ||
						event.key.code == sf::Keyboard::S) &&
						!inLunge)
					{
						inLunge = true;
					}
					if ((event.key.code == sf::Keyboard::Down ||
						event.key.code == sf::Keyboard::S) &&
						!inLunge)
					{
						inLunge = true;
					}
					if ((event.key.code == sf::Keyboard::Down ||
						event.key.code == sf::Keyboard::S) &&
						(event.key.code == sf::Keyboard::Right ||
						event.key.code == sf::Keyboard::D) &&
						!inLunge)
					{
						inLunge = true;
					}
					if ((event.key.code == sf::Keyboard::Right ||
						event.key.code == sf::Keyboard::D) &&
						!inLunge)
					{
						inLunge = true;
					}

			}
		}


		bug0.update(allPoints, deltaTime);
		bug1.update(allPoints, deltaTime);
		bug2.update(allPoints, deltaTime);

		window.clear(sf::Color::Black);

		window.draw(bgSprite);

		sf::RectangleShape rect(sf::Vector2f(5.0f, 5.0f));
		rect.setFillColor(sf::Color::Red);
		for (int i = 0; i < 18; ++i)
		{
			rect.setPosition(allPoints[i].getPosition());
			window.draw(rect);
		}

		bug0.draw(window);
		bug1.draw(window);
		bug2.draw(window);

		window.display();
	}

	return 0;
}
