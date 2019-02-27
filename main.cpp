#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<fstream>
#include<sstream>
#include"player1.h"
#include "maingame.h"
#include "Menu.h"
#include "files.h"


using namespace std;
using namespace sf;
int main()
{
	string ch;
	bool b = false;
	Readfile rd;
	menu m;
	mainGame mm;

	do
	{
		
		int n = m.showoptions();
		switch (n)
		{
		case 1:
			mm.start();
			break;
		case 2:
			ch = "about.txt";
			rd.read(ch, "About");
			break;
		case 3:
			ch = "help.txt";
			rd.read(ch, "Help");
			break;
		default:
			b = true;
			break;
		}
	} while (b);
	return 0;
}