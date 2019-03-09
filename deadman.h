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
#include"player1.h"

using namespace sf;

class deadman
{
public:
	Sprite shapedead;
	Texture texturedead;
	

	deadman(Texture *texturedead, int x,int y)
	{
		this->shapedead.setTexture(*texturedead);
		this->shapedead.setPosition(x,y);

	}

};