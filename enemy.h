#pragma once
#include<SFML\Graphics.hpp>
#include"arrow.h"


class Enemy {
public:
	Enemy(sf::Vector2f size) {
		enemy.setSize(size);
		enemy.setFillColor(sf::Color::Yellow);
	}
	void setpos(sf::Vector2f newpos) {
		enemy.setPosition(newpos);
	}
	void checkcoll(Bullet bullet) {
		if (bullet.getRight() > enemy.getPosition().x && bullet
			.getTop() < enemy.getPosition().y +enemy.getSize().y
			&& bullet.getBottom() > enemy.getPosition().y) {
			enemy.setPosition(sf::Vector2f(45455, 54545));

		}
	}
	void draw(sf::RenderWindow &window) {
		window.draw(enemy);
	}
	

private: 
	sf::RectangleShape enemy;

};