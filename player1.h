#pragma once
#include<SFML\Graphics.hpp>
#include <SFML/Graphics.hpp>
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include"SFML\Audio.hpp"
#include<iostream>
#include<math.h>
#include<cstdlib>
#include<vector>


using namespace sf;



class arrow
{
public:
	Sprite shape;

	arrow(Texture *texture, Vector2f(pos))
	{

		this->shape.setTexture(*texture);
		this->shape.setScale(1.f, 01.f);


		this->shape.setPosition(pos);

		this->shape.setRotation(03.f);

	}


};


class player
{
public:
	Sprite shape;

	Texture* texture;



	std::vector<arrow> arrows;


	player(Texture *texture)
	{


		this->texture = texture;
		this->shape.setTexture(*texture);

		this->shape.setPosition(0.0f, 400.f);///player posiyion
		this->shape.setScale(1.0f, 1.f);
		this->shape.setOrigin(shape.getPosition().x / 5, shape.getPosition().y / 6);
	}






};

class enemy
{
public:
	Sprite shape;


	enemy(Texture *texture, Vector2u windowsize) {


		this->shape.setTexture(*texture);
		this->shape.setPosition(windowsize.x - this->shape.getGlobalBounds().width, rand() % (int)(windowsize.y - this->shape.getGlobalBounds().height));
	}


	~enemy() {};

};