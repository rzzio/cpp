#pragma once
#include<SFML\Graphics.hpp>

class animation
{
public:
	animation(sf::Texture * texture,sf::Vector2u imagecount,float switchtime);
	~animation();

	void update(int row, float deltatime);
		 

public:
	sf::IntRect uvrect;


private:
	
	sf::Vector2u switchtime;
	sf::IntRect uvrect;
	sf::Vector2u imagecount;

	float switchtime;
	float totaltime;


	
	
	


	
};

