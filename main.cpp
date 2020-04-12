#include <SFML\Graphics.hpp>
#include <iostream>

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


	sf::Texture bug;
	bug.loadFromFile("png/bug_sheet.png");
	sf::Sprite bugSprite;
	bugSprite.setTexture(bug);
	//bugSprite.setScale(10.0f, 10.0f);

	bool inLunge;

	while (window.isOpen())
	{
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
					if ((event.key.code == sf::Keyboard::Right ||
						event.key.code == sf::Keyboard::D) &&
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

			}
		}

		window.clear(sf::Color::Black);

		window.draw(bgSprite);
		window.draw(bugSprite);

		window.display();
	}

	return 0;
}