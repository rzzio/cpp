#include<SFML\Audio.hpp>
#include"deadman.h"

using namespace std;
using namespace sf;
class mainGame
{

public:
	bool start()
	{


		srand(time(NULL));
		sf::RenderWindow window;
		window.create(VideoMode(1920, 1080), "archerman", Style::Titlebar | Style::Close);
		window.setFramerateLimit(60);
		sf::Texture texture;
		if (!texture.loadFromFile("bg.png"))
			std::cout << "failed load";
		sf::Sprite bg;
		bg.setTexture(texture);

		sf::Music sound3;
		sound3.openFromFile("11.wav");
		sound3.setVolume(10.f);
		sound3.play();





		sf::SoundBuffer shoot;
		shoot.loadFromFile("laser.wav");   //shooting sound
		sf::Sound sound;
		sound.setBuffer(shoot);

		sf::SoundBuffer gameovers;
		gameovers.loadFromFile("over.wav");      //game over sound
		sf::Sound sound2;
		sound2.setBuffer(gameovers);






		Font font;     //making my font 
		font.loadFromFile("28 Days Later.ttf");

		//init textures
		Texture playertex;
		playertex.loadFromFile("archer2.png");


		Texture enemytex;
		enemytex.loadFromFile("enemy.png"); //-----------------------------------------


		Texture earrow;
		earrow.loadFromFile("earrow.png");


		Texture arrowtex;
		arrowtex.loadFromFile("arrow.png");

		Texture deadtex;
		deadtex.loadFromFile("deadman.png");

		Texture injured1tex;
		injured1tex.loadFromFile("injured1.png");

		Texture injured2tex;
		injured2tex.loadFromFile("injured2.png");



		Texture dietex;
		dietex.loadFromFile("die.png");






		player player2(&enemytex); //making 2nd player
		int score2 = 100;
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
		scoretext2.setFillColor(Color::Green);
		scoretext2.setPosition(1500.f, 10.f);


		Text winner;
		winner.setFont(font);
		winner.setCharacterSize(200);
		winner.setPosition(750.f, 750.f);




		//player init
		int score = 100;                            //making 1st player
		player player(&playertex);





		int shoottimer = 50;



		//init enimies

		std::vector<enemy> enemies;


		Text gameover;
		gameover.setFont(font);
		gameover.setCharacterSize(200);
		gameover.setFillColor(Color::Black);
		gameover.setPosition(250.f, 250.f);
		gameover.setString("GAME   OVER");



		player2.shape.move(1800.f, 350.f);



		while (window.isOpen())
		{




			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

			}


			if (score > 5 && score2>5)
				//update player
			{

				{
					deadman injured1(&injured1tex, player.shape.getPosition().x, player.shape.getPosition().y);
					deadman injured2(&injured2tex, player2.shape.getPosition().x, player2.shape.getPosition().y);



					//making 1st player move

					if (Keyboard::isKeyPressed(Keyboard::W))
						player.shape.move(0.f, -10.f);

					//if (Keyboard::isKeyPressed(Keyboard::A))
					//player.shape.move(-10.f, 0.f);

					if (Keyboard::isKeyPressed(Keyboard::S))
						player.shape.move(0.f, 10.0f);

					//if (Keyboard::isKeyPressed(Keyboard::D))
					//player.shape.move(10.f, 0.f);




					//making 2nd player move___________________________________________________________________

					if (Keyboard::isKeyPressed(Keyboard::Up))
						player2.shape.move(0.f, -10.f);

					//if (Keyboard::isKeyPressed(Keyboard::Left))      //extra movement if needed
					//player2.shape.move(-10.f, 0.f);

					if (Keyboard::isKeyPressed(Keyboard::Down))
						player2.shape.move(0.f, 10.0f);

					//if (Keyboard::isKeyPressed(Keyboard::Right))
					//player2.shape.move(10.f, 0.f);




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

					// arrows of player 1
					if (shoottimer < 40)
					{
						shoottimer++;
					}
					if (Keyboard::isKeyPressed(Keyboard::Space) && shoottimer >= 40)

					{
						player.arrows.push_back(arrow(&arrowtex, player.shape.getPosition()));
						shoottimer = 0;
					}
					// arrows



					//______________________________________________________ arrows of player 2


					if (shoottimer2 < 40)
					{
						shoottimer2++;
					}
					if (Keyboard::isKeyPressed(Keyboard::Numpad0) && shoottimer2 >= 40)
					{
						player2.arrows.push_back(arrow(&earrow, player2.shape.getPosition()));
						shoottimer2 = 0;
					}

					if (shoottimer2 < 15)
					{
						shoottimer2++;
					}

					//____________________________________________________



					//arrows window collision of player 1
					for (size_t i = 0; i < player.arrows.size(); i++)
					{
						//move arrows
						player.arrows[i].shape.move(20.0F, 1.F);
						if (player.arrows[i].shape.getPosition().x > window.getSize().x)
						{
							player.arrows.erase(player.arrows.begin() + i);
							break;
						}
						if (player.arrows[i].shape.getGlobalBounds().intersects(player2.shape.getGlobalBounds()))
						{
							score2 = score2 - 10;

							//player2.shape.setColor(Color::Transparent);




							player2.shape.setScale(player2.shape.getScale().x - .05f, player2.shape.getScale().y - .05f);   //twisterrrrrrrrrrrrrrr





							sound.play();

							player.arrows.erase(player.arrows.begin() + i);

							break;

						}






					}

					//arrow window colliosn of player 2________________________
					for (size_t i = 0; i < player2.arrows.size(); i++)
					{
						//move arrows
						player2.arrows[i].shape.move(-20.0F, 1.F);
						if (player2.arrows[i].shape.getPosition().x > window.getSize().x)
						{
							player2.arrows.erase(player2.arrows.begin() + i);
							break;
						}

						if (player2.arrows[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
						{
							score = score - 10;
							sound.play();
							player.shape.setScale(player.shape.getScale().x - .05f, player.shape.getScale().y - .05f);   //twisterrrrrrrrrrrrrrr


							player2.arrows.erase(player2.arrows.begin() + i);




							break;


						}




						//enemy collis

					}

					//__



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

							break;

						}
					}

					//UI update
					scoretext.setString("HEALTH  " + std::to_string(score));
					scoretext2.setString("HEALTH  " + std::to_string(score2));

				}


				//============================================================================//



				//draw 
				window.clear();
				window.draw(bg);











				//arrows
				for (size_t i = 0; i < player.arrows.size(); i++)
				{
					window.draw(player.arrows[i].shape);



				}

				//arrows of player 2

				for (size_t i = 0; i < player2.arrows.size(); i++)
				{
					window.draw(player2.arrows[i].shape);
				}


				//UI
				window.draw(scoretext);
				window.draw(scoretext2);

				deadman deadman2(&deadtex, player2.shape.getPosition().x - 90, player2.shape.getPosition().y);
				deadman deadman1(&deadtex, player.shape.getPosition().x, player.shape.getPosition().y);




				//winner printing

				if (score2 < 10)
				{
					winner.setFillColor(Color::Red);

					winner.setString("PLAYER1 WINS");

					player2.shape.setColor(Color::Transparent);


					window.draw(deadman2.shapedead);

				}
				if (score < 10)
				{
					winner.setFillColor(Color::Green);
					winner.setString("PLAYER2 WINS");
					player.shape.setColor(Color::Transparent);
					window.draw(deadman1.shapedead);

				}
				window.draw(player.shape);
				window.draw(player2.shape);







				if (score < 10 || score2 < 10)
				{



					window.draw(gameover);
					window.draw(winner);

					sound3.pause();     //stopping bg sound
					sound2.play();    //gameover sound


				}


				window.display();



			}
		}

		return 0;

	}

};



