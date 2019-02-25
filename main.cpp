#include <SFML/Graphics.hpp>
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include<iostream>
#include<math.h>
#include<cstdlib>
#include<vector>

using namespace sf;

class bullet
{
public:
	Sprite shape;

	bullet(Texture *texture, Vector2f pos)
	{
		this->shape.setTexture(*texture);
		this->shape.setScale(0.8f, 0.8f);
		this->shape.setPosition(pos);

	}


};


class player
{
public:
	Sprite shape;
	Texture* texture;

	int hp;
	int hpmax;

	std::vector<bullet> bullets;


	player(Texture *texture)
	{
		this->hpmax = 10;
		this->hp = this->hpmax;

		this->texture = texture;
		this->shape.setTexture(*texture);

		this->shape.setPosition(0.0f, 0.0f);       ///player posiyion


	}





};

class enemy
{
public:
	Sprite shape;
	int hp;
	int hpmax;

	enemy(Texture *texture, Vector2u windowsize) {

		this->hpmax = rand() % 3 + 1;
		this->hp = this->hpmax;

		this->shape.setTexture(*texture);
		this->shape.setPosition(windowsize.x - this->shape.getGlobalBounds().width, rand() % (int)(windowsize.y - this->shape.getGlobalBounds().height));
	}
	~enemy() {};

};




int main()

{
	srand(time(NULL));

	sf::RenderWindow window;

	window.create(VideoMode(1500, 700), "archerman", Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);

	Font font;     //making my font 
	font.loadFromFile("28 Days Later.ttf");

	//init textures
	Texture playertex;
	playertex.loadFromFile("archer.png");

	Texture enemytex;
	enemytex.loadFromFile("enemy.png");

	Texture bullettex;
	bullettex.loadFromFile("arrow.png");

	//displaying scoretext
	Text scoretext;
	scoretext.setFont(font);
	scoretext.setCharacterSize(25);
	scoretext.setFillColor(Color::Red);
	scoretext.setPosition(10.f, 10.f);

	//player init
	int score = 0;
	player player(&playertex);
	int shoottimer = 25;

	Text hptext;
	hptext.setFont(font);
	hptext.setCharacterSize(12);
	//hptext.setColor(Color::White);

	//init enimies
	int enemyspawntimer = 5;
	std::vector<enemy> enemies;

	Text ehptext;
	ehptext.setFont(font);
	ehptext.setCharacterSize(12);
	//ehptext.setColor(Color::White);

	Text gameover;
	gameover.setFont(font);
	gameover.setCharacterSize(90);
	gameover.setFillColor(Color::Red);
	gameover.setPosition(100.f, window.getSize().y/2);
	gameover.setString("GAME OVER BUDDY");




	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();




		}

		//update player
		if (player.hp > 0)
		{




			if (Keyboard::isKeyPressed(Keyboard::W))
				player.shape.move(0.f, -10.f);

			if (Keyboard::isKeyPressed(Keyboard::A))
				player.shape.move(-10.f, 0.f);

			if (Keyboard::isKeyPressed(Keyboard::S))
				player.shape.move(0.f, 10.0f);

			if (Keyboard::isKeyPressed(Keyboard::D))
				player.shape.move(10.f, 0.f);

			hptext.setPosition(player.shape.getPosition().x, player.shape.getPosition().y - hptext.getGlobalBounds().height);
			hptext.setString(std::to_string(player.hp) + "/" + std::to_string(player.hpmax));


			//collison with window

			if (player.shape.getPosition().x <= 0) //left 
				player.shape.setPosition(0.f, player.shape.getPosition().y);
			if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width) //right
				player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
			if (player.shape.getPosition().y <= 0) //top
				player.shape.setPosition(player.shape.getPosition().x, 0.0f);
			if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height) //bottom
				player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);




			//update comtrol

			// bullets
			if (shoottimer < 30)
			{
				shoottimer++;
			}
			if (Keyboard::isKeyPressed(Keyboard::Space) && shoottimer >= 30)
			{
				player.bullets.push_back(bullet(&bullettex, player.shape.getPosition()));
				shoottimer = 0;
			}


			// bullets



			if (shoottimer < 15)
			{
				shoottimer++;
			}

			//bullets window collision
			for (size_t i = 0; i < player.bullets.size(); i++)
			{
				//move bullets
				player.bullets[i].shape.move(20.0F, 0.0F);
				if (player.bullets[i].shape.getPosition().x > window.getSize().x)
				{
					player.bullets.erase(player.bullets.begin() + i);
					break;
				}



				//enemy collision
				for (size_t k = 0; k < enemies.size(); k++)
				{

					if (player.bullets[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds()))
					{
						if (enemies[k].hp <= 1)
						{
							score += enemies[k].hpmax;
							enemies.erase(enemies.begin() + k);
						}
						else
							enemies[k].hp--;
						player.bullets.erase(player.bullets.begin() + i);
						break;

					}

				}
			}



			//enemy update
			if (enemyspawntimer < 20)   //ENEMY SPAWN
				enemyspawntimer++;


			if (enemyspawntimer >= 20)
			{

				enemies.push_back(enemy(&enemytex, window.getSize()));
				enemyspawntimer = 0;
			}



			for (size_t i = 0; i < enemies.size(); i++)
			{
				enemies[i].shape.move(-7.4f, 0.f);

				if (enemies[i].shape.getPosition().x <= 0 - enemies[i].shape.getGlobalBounds().width)
				{
					enemies.erase(enemies.begin() + i);
					break;
				}
				if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{
					enemies.erase(enemies.begin() + i);
					player.hp--; //player health decreasing
					break;

				}
			}

			//UI update
			scoretext.setString("Score=" + std::to_string(score));

		}

		//============================================================================//



		//draw 
		window.clear();

		
		window.draw(player.shape);

		//bullets
		for (size_t i = 0; i < player.bullets.size(); i++)
		{
			window.draw(player.bullets[i].shape);
		}

		//enemy
		for (size_t i = 0; i<enemies.size(); i++)
		{
			ehptext.setString(std::to_string(enemies[i].hp) + "/" + std::to_string(enemies[i].hpmax));
			ehptext.setPosition(enemies[i].shape.getPosition().x, enemies[i].shape.getPosition().y-ehptext.getGlobalBounds().height);
			window.draw(ehptext);
			window.draw(enemies[i].shape);
		}

		//UI
		window.draw(scoretext);
		window.draw(hptext);

		if (player.hp <= 0)
			window.draw(gameover);

		window.display();



	}

	return 0;
}