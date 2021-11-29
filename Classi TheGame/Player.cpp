#include "Player.h"

Player::Player(int health, int attack) {
	_health = health;
	_attack = attack;
	_points = 0;
}

void Player::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Player::getPosition(int& x, int& y) {
	x = _x;
	y = _y;
}

// int Player::attack() { }

// void Player::addPoints(int points) { }

// int Player::takeDamage(int attack) {	}
