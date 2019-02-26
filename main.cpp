#include <SFML/Graphics.hpp>

#include"player1.h"

using namespace sf;


int main()

{
	srand(time(NULL));
	sf::RenderWindow window;
	window.create(VideoMode(1920, 1080), "archerman", Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);
	sf::Texture texture;
	if (!texture.loadFromFile("backimg.png"))
		std::cout << "failed load";
	sf::Sprite bg;
	bg.setTexture(texture);


	Font font;     //making my font 
	font.loadFromFile("28 Days Later.ttf");

	//init textures
	Texture playertex;
	playertex.loadFromFile("archer.png");


	Texture enemytex;
	enemytex.loadFromFile("enemy.png");

	Texture earrow;
	earrow.loadFromFile("earrow.png");


	Texture bullettex;
	bullettex.loadFromFile("arrow.png");

	player player2(&enemytex); //making 2nd player
	int score2 = 0;
	int shoottimer2 = 50;
    

	//displaying scoretext
	Text scoretext;                             //score of player 1
	scoretext.setFont(font);
	scoretext.setCharacterSize(80);
	scoretext.setFillColor(Color::Red);
	scoretext.setPosition(10.f, 10.f);


	Text scoretext2;
	scoretext2.setFont(font);                  //score of player 2
	scoretext2.setCharacterSize(80);
	scoretext2.setFillColor(Color::Blue);
	scoretext2.setPosition(1600.f, 10.f);


	Text winner;
	winner.setFont(font);
	winner.setCharacterSize(200);
	winner.setPosition(750.f, 750.f);




	//player init
	int score = 0;                            //making 1st player
	player player(&playertex);
	int shoottimer = 40;

	Text hptext;
	hptext.setFont(font);
	hptext.setCharacterSize(12);
	//hptext.setColor(Color::White);

	//init enimies
	int enemyspawntimer = 5;
	std::vector<enemy> enemies;

	Text ehptext;
	ehptext.setFont(font);
	ehptext.setCharacterSize(20);
	//ehptext.setColor(Color::White);

	Text gameover;
	gameover.setFont(font);
	gameover.setCharacterSize(200);
	gameover.setFillColor(Color::Black);
	gameover.setPosition(100.f, player.shape.getPosition().x / 2);
	gameover.setString("GAME OVER BUDDY");




	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}

		if (score <= 10)
			//update player
		{
			{


				//making 1st player move

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

				//making 2nd player move___________________________________________________________________

				if (Keyboard::isKeyPressed(Keyboard::Up))
					player2.shape.move(0.f, -10.f);

				if (Keyboard::isKeyPressed(Keyboard::Left))
					player2.shape.move(-10.f, 0.f);

				if (Keyboard::isKeyPressed(Keyboard::Down))
					player2.shape.move(0.f, 10.0f);

				if (Keyboard::isKeyPressed(Keyboard::Right))
					player2.shape.move(10.f, 0.f);

				hptext.setPosition(player2.shape.getPosition().x, player2.shape.getPosition().y - hptext.getGlobalBounds().height);
				hptext.setString(std::to_string(player2.hp) + "/" + std::to_string(player2.hpmax));



				//_____________________________________________________________________________________________


				//collison with window of player1

				if (player.shape.getPosition().x <= 0) //left 
					player.shape.setPosition(0.f, player.shape.getPosition().y);
				if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width) //right
					player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
				if (player.shape.getPosition().y <= 0) //top
					player.shape.setPosition(player.shape.getPosition().x, 0.0f);
				if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height) //bottom
					player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);




				//collison with window of player 2_______________________________

				if (player2.shape.getPosition().x <= 0) //left 
					player2.shape.setPosition(0.f, player2.shape.getPosition().y);
				if (player2.shape.getPosition().x >= window.getSize().x - player2.shape.getGlobalBounds().width) //right
					player2.shape.setPosition(window.getSize().x - player2.shape.getGlobalBounds().width, player2.shape.getPosition().y);
				if (player2.shape.getPosition().y <= 0) //top
					player2.shape.setPosition(player2.shape.getPosition().x, 0.0f);
				if (player2.shape.getPosition().y >= window.getSize().y - player2.shape.getGlobalBounds().height) //bottom
					player2.shape.setPosition(player2.shape.getPosition().x, window.getSize().y - player2.shape.getGlobalBounds().height);



				//______________________________________________________________









				//update comtrol

				// bullets of player 1
				if (shoottimer < 40)
				{
					shoottimer++;
				}
				if (Keyboard::isKeyPressed(Keyboard::Space) && shoottimer >= 40)

				{
					player.bullets.push_back(bullet(&bullettex, player.shape.getPosition()));
					shoottimer = 0;
				}
				// bullets



				//______________________________________________________ bullets of player 2


				if (shoottimer2 < 40)
				{
					shoottimer2++;
				}
				if (Keyboard::isKeyPressed(Keyboard::Numpad0) && shoottimer2 >= 40)
				{
					player2.bullets.push_back(bullet(&earrow, player2.shape.getPosition()));
					shoottimer2 = 0;
				}

				if (shoottimer2 < 15)
				{
					shoottimer2++;
				}

				//____________________________________________________



				//bullets window collision of player 1
				for (size_t i = 0; i < player.bullets.size(); i++)
				{
					//move bullets
					player.bullets[i].shape.move(20.0F, 5.F);
					if (player.bullets[i].shape.getPosition().x > window.getSize().x)
					{
						player.bullets.erase(player.bullets.begin() + i);
						break;
					}
					if (player.bullets[i].shape.getGlobalBounds().intersects(player2.shape.getGlobalBounds()))
					{
						score++;

						player.bullets.erase(player.bullets.begin() + i);
						break;

					}





				}

				//bullet window colliosn of player 2________________________
				for (size_t i = 0; i < player2.bullets.size(); i++)
				{
					//move bullets
					player2.bullets[i].shape.move(-20.0F, -5.F);
					if (player2.bullets[i].shape.getPosition().x > window.getSize().x)
					{
						player2.bullets.erase(player2.bullets.begin() + i);
						break;
					}

					if (player2.bullets[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
					{
						score2++;

						player2.bullets.erase(player2.bullets.begin() + i);
						break;

					}




					//enemy collision

				}

				//________________________________________________



				//enemy update
				if (enemyspawntimer < 50)   //ENEMY SPAWN
					enemyspawntimer++;


				if (enemyspawntimer >= 1000)
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
				scoretext.setString("Score  " + std::to_string(score));
				scoretext2.setString("Score  " + std::to_string(score2));

			}


			//============================================================================//



			//draw 
			window.clear();
			window.draw(bg);




			window.draw(player.shape);
			window.draw(player2.shape);




			//bullets
			for (size_t i = 0; i < player.bullets.size(); i++)
			{
				window.draw(player.bullets[i].shape);

			}

			//bullets of player 2

			for (size_t i = 0; i < player2.bullets.size(); i++)
			{
				window.draw(player2.bullets[i].shape);
			}


			//UI
			window.draw(scoretext);
			window.draw(scoretext2);
			

			//winner printing
			
			if (score >= 9)
			{
				winner.setFillColor(Color::Red);

				winner.setString("PLAYER1 WINS");
			}
			if (score2 >= 10)
			{
				winner.setFillColor(Color::Blue);
				winner.setString("PLAYER2 WINS");
			}




			if (score >= 10 || score2 >= 10)
			{
				window.draw(gameover);
				window.draw(winner);
			}

			window.display();



		}
	}

	return 0;
}