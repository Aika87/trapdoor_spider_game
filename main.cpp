#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "Animation.h"

using std::cout;

static const int WINDOW_WIDTH = 1600;
static const int WINDOW_HEIGHT = 900;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Trapdoor", sf::Style::Default);
	window.setVerticalSyncEnabled(true);

	// Sprites to do: Spider, energy bar

	sf::Texture bg;
	bg.loadFromFile("png/background.png");
	sf::Sprite bgSprite;
	bgSprite.setTexture(bg);
	bgSprite.setScale(10.0f, 10.0f);


	sf::Texture lady;
	lady.loadFromFile("png/lady.png");
	sf::Sprite ladySprite;
	ladySprite.setTexture(lady);
	ladySprite.setScale(10.0f, 10.0f);

	Animation animation(&lady, sf::Vector2u(3, 1), 0.3f);
	float deltaTime = 0.0f;
	sf::Clock clock;

	sf::Texture beetle;
	beetle.loadFromFile("png/beetle.png");
	sf::Sprite beetleSprite;
	beetleSprite.setTexture(beetle);
	beetleSprite.setScale(10.0f, 10.0f);

	sf::Texture worm;
	worm.loadFromFile("png/worm.png");
	sf::Sprite wormSprite;
	wormSprite.setTexture(worm);
	wormSprite.setScale(10.0f, 10.0f);

	bool inLunge = false;

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

		animation.update(0, deltaTime);
		ladySprite.setTextureRect(animation.uvRect);

		window.clear(sf::Color::Black);

		window.draw(bgSprite);
		window.draw(ladySprite);

		window.display();
	}

	return 0;
}
