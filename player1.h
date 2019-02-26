#pragma once
#pragma once
#pragma once

#include <SFML/Graphics.hpp>
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include"SFML\Audio.hpp"
#include<iostream>
#include<math.h>
#include<cstdlib>
#include<vector>


using namespace sf;


class bullet
{
public:
	Sprite shape;

	bullet(Texture *texture, Vector2f(pos))
	{
		this->shape.setTexture(*texture);
		this->shape.setScale(2.3f, 01.f);


		this->shape.setPosition(pos);

		this->shape.setRotation(8.f);

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

		this->shape.setPosition(0.0f, 0.0f);///player posiyion
		this->shape.setScale(1.0f, 1.f);
		this->shape.setOrigin(shape.getPosition().x / 5, shape.getPosition().y / 6);
	}





};

class enemy
{
public:
	Sprite shape;
	int hp;
	int hpmax;

	enemy(Texture *texture, Vector2u windowsize) {

		this->hpmax = rand() % 1 + 1;
		this->hp = this->hpmax;

		this->shape.setTexture(*texture);
		this->shape.setPosition(windowsize.x - this->shape.getGlobalBounds().width, rand() % (int)(windowsize.y - this->shape.getGlobalBounds().height));
	}


	~enemy() {};

};




















