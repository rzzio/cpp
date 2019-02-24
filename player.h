#pragma once

#include<SFML\Graphics.hpp>


class Player {

public:
	void setPos(sf::Vector2f newpos) {
		player.setPosition(newpos);
		player.setFillColor(sf::Color::Red);
	}
	Player(sf::Vector2f size) {
		player.setSize(size);
	}

	void move(sf::Vector2f dir) {
		player.move(dir);
	}
	int getX() {
		return player.getPosition().x;

	}
	int getY() {
		return player.getPosition().y;

	}
	void draw(sf::RenderWindow &window) {
		window.draw(player);
	}
private:
	sf::RectangleShape player;
};