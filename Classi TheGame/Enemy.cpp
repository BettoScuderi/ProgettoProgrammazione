#include "Enemy.h"


Enemy::Enemy(/*int attack,*/ int health, int pointsValue)
{
	//_attack = attack; LA PASSIAMO SINGOLARMENTE NELLE SOTTOCLASSI
	_health = health;
	_pointsValue = pointsValue;
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
