#include <SFML/Graphics.hpp>
#include"arrow.h"
#include"enemy.h"
#include"player.h"
#include<vector>


int main()
{

	sf::RenderWindow window;
	sf::Vector2i centerWidow((sf::VideoMode::getDesktopMode().width / 2) - 755, (sf::VideoMode::getDesktopMode().height / 2 - 390));
	//sf::RenderWindow window(sf::VideoMode(500, 500), "ARCHERMAN");

	window.create(sf::VideoMode(1500, 700), "archerman", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWidow);

	window.setKeyRepeatEnabled(true);
	bool isfiring = false;
	
	Player player(sf::Vector2f(50, 50)); //players
	Enemy enemy(sf::Vector2f(50, 50));
	


	std::vector<Bullet> bullectVec;  //storing bullet

	enemy.setpos(sf::Vector2f(500, 50));
	player.setPos(sf::Vector2f(550, 200));


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			int moveSpeed = 4;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				player.move(sf::Vector2f(0, -moveSpeed));
			}
			 if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				 player.move(sf::Vector2f(0, moveSpeed));
			 }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
				player.move(sf::Vector2f(-moveSpeed, 0));
			}
			 if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { 
				player.move(sf::Vector2f(moveSpeed, 0));
			}
				

			 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				 isfiring = true;

			}
			


		}
		if (isfiring == true) {
			Bullet newbullet(sf::Vector2f(50, 5));
			newbullet.setpos(sf::Vector2f(player.getX(), player.getY()));
			bullectVec.push_back(newbullet);
			isfiring = false;

		}
		for (int i = 0; i < bullectVec.size(); i++) {
			bullectVec[i].draw(window);
			bullectVec[i].fire(3);
		}
		for (int i = 0; i < bullectVec.size(); i++) {
			enemy.checkcoll(bullectVec[i]); 
		}

		window.clear();
	
		player.draw(window);
 	
		enemy.draw(window);
		window.display();
	}

	return 0;
}