#include "Player.h"

Player::Player() {
	// _x = start_x
	// _y = start_y
}

void Player::init(int level, int health, int attack, int defense, int experience) {
	_level = level;
	_health = health;
	_attack = attack;
	_defense = defense;
	_exp = experience;
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

// void Player::addExperience(int experience) { }

// int Player::takeDamage(int attack) {	}