#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "Animation.h"
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
	float widthRatio = float(WINDOW_WIDTH / bgx);
	float heightRatio = float(WINDOW_HEIGHT / bgy);
	bgSprite.setScale(1.0f * widthRatio, 1.0f * heightRatio);

	//Path Points
	Point pointA(10.0f * widthRatio, 50.0f * heightRatio),
		pointB(47.0f * widthRatio, 43.0f * heightRatio),
		pointC(130.0f * widthRatio, 42.0f * heightRatio),
		pointD(146.0f * widthRatio, 31.0f * heightRatio),
		pointE(39.0f * widthRatio, 65.0f * heightRatio),
		pointF(72.0f * widthRatio, 75.0f * heightRatio),
		pointG(85.0f * widthRatio, 62.0f * heightRatio),
		pointH(115.0f * widthRatio, 65.0f * heightRatio),
		pointI(137.0f * widthRatio, 60.0f * heightRatio),
		pointJ(30.0f * widthRatio, 78.0f * heightRatio),
		pointK(145.0f * widthRatio, 76.0f * heightRatio),
		pointS1(-20.0f * widthRatio, 45.0f * heightRatio),
		pointS2(26.0f * widthRatio, 110.0f * heightRatio),
		pointS3(51.0f * widthRatio, 110.0f * heightRatio),
		pointS4(95.0f * widthRatio, 110.0f * heightRatio),
		pointS5(135.0f * widthRatio, 110.0f * heightRatio),
		pointS6(180.0f * widthRatio, 70.0f * heightRatio),
		pointS7(180.0f * widthRatio, 42.0f * heightRatio);

	//path connections
	pointS1.connect(pointA);

	pointA.connect(pointS1);
	pointA.connect(pointB);
	pointA.connect(pointE);
	pointA.connect(pointJ);
	pointA.connect(pointS2);

	pointB.connect(pointA);
	pointB.connect(pointE);
	pointB.connect(pointF);
	pointB.connect(pointG);
	pointB.connect(pointC);

	pointC.connect(pointB);
	pointC.connect(pointD);
	pointC.connect(pointH);
	pointC.connect(pointI);

	pointD.connect(pointC);
	pointD.connect(pointI);
	pointD.connect(pointK);
	pointD.connect(pointS7);

	pointE.connect(pointA);
	pointE.connect(pointB);
	pointE.connect(pointF);
	pointE.connect(pointJ);

	pointF.connect(pointB);
	pointF.connect(pointE);
	pointF.connect(pointG);
	pointF.connect(pointJ);
	pointF.connect(pointS3);
	pointF.connect(pointS4);

	pointG.connect(pointB);
	pointG.connect(pointF);
	pointG.connect(pointH);
	pointG.connect(pointS4);

	pointH.connect(pointG);
	pointH.connect(pointC);
	pointH.connect(pointI);
	pointH.connect(pointS4);
	pointH.connect(pointS5);

	pointI.connect(pointC);
	pointI.connect(pointH);
	pointI.connect(pointD);
	pointI.connect(pointK);
	pointI.connect(pointS5);

	pointJ.connect(pointA);
	pointJ.connect(pointE);
	pointJ.connect(pointF);
	pointJ.connect(pointS2);
	pointJ.connect(pointS3);

	Point* pointArray[] = 
	{ 
		&pointA, &pointB, &pointC, &pointD, &pointE, &pointF, &pointG, &pointH, 
		&pointI, &pointJ, &pointK,
		&pointS1, &pointS2, &pointS3, &pointS4, &pointS5, &pointS6, &pointS7
	};

	// edges within range: B to E, B to F, B to G, G to F, G to S4, G to H,
	// H to C, H to S4, H to I, H to S5, D to I

	sf::Texture lady;
	lady.loadFromFile("png/lady.png");
	sf::Sprite ladySprite;
	ladySprite.setTexture(lady);
	ladySprite.setScale(5.0f, 5.0f);
	ladySprite.setPosition(pointI.getPosition());

	sf::Texture beetle;
	beetle.loadFromFile("png/beetle.png");
	sf::Sprite beetleSprite;
	beetleSprite.setTexture(beetle);
	beetleSprite.setScale(5.0f, 5.0f);
	beetleSprite.setPosition(pointE.getPosition());

	sf::Texture worm;
	worm.loadFromFile("png/worm.png");
	sf::Sprite wormSprite;
	wormSprite.setTexture(worm);
	wormSprite.setScale(5.0f, 5.0f);
	wormSprite.setPosition(pointA.getPosition());

	Animation animationLady(&lady, sf::Vector2u(4, 1), 0.3f);
	Animation animationBeetle(&beetle, sf::Vector2u(3, 1), 0.05f);
	Animation animationWorm(&worm, sf::Vector2u(4, 1), 0.5f);
	float deltaTime = 0.0f;
	sf::Clock clock;

	bool inLunge = false;

	for (int i = 0; i < 18; ++i)
	{
		cout << pointArray[i]->getPosition().x;
		cout << "\n";
	}

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

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

		animationLady.update(0, deltaTime, true);
		animationBeetle.update(0, deltaTime, false);
		animationWorm.update(0, deltaTime, false);
		ladySprite.setTextureRect(animationLady.uvRect);
		beetleSprite.setTextureRect(animationBeetle.uvRect);
		wormSprite.setTextureRect(animationWorm.uvRect);

		window.clear(sf::Color::Black);

		window.draw(bgSprite);
		window.draw(ladySprite);
		window.draw(beetleSprite);
		window.draw(wormSprite);

		window.display();
	}

	return 0;
}
