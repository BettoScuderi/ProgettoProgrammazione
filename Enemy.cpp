#include "Enemy.h"


Enemy::Enemy(string name, char tile, int level, int attack, int defense, int health, int xp)
{
	_name = name;
	_tile = tile;
	_level = level;
	_attack = attack;
	_defense = defense;
	_health = health;
	_expValue = xp;
}


void Enemy::setPosition(int x, int y) {
	_x = x;
	_y = y;
}


void Enemy::getPosition(int& x, int& y) {
	x = _x;
	y = _y;

}

// int Enemy::attack() { }

// int Enemy::takeDamage(int attack) { }

// Enemy::getMove(int playerX, int playerY) { }