#include<SFML\Graphics.hpp>
#include<iostream>
#include"animation.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 1080), "archer man", sf::Style::Close | sf::Style::Resize);
	sf::RectangleShape player(sf::Vector2f(200.0f, 300.0f));
	player.setPosition(100.0f, 775.0f);
	sf::Texture playertexture;
	playertexture.loadFromFile("archer.png");
	player.setTexture(&playertexture);

	animation animation(&playertexture, sf::Vector2u(3, 9), 0.3f);

	float deltatime = 0.0f;
	sf::Clock clock;




		
	
	while (window.isOpen())
	{
		deltatime =clock.restart().asSeconds;
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
			//animation.update(0, deltatime);
			//player.setTextureRect(animation.uvrect);

			window.clear();
			window.draw(player);
			window.display();
			getchar();

		}
		getchar();
		return 0;

	}



}
