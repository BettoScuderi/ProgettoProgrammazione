#pragma once
#include "Player.h"
#include "Enemy.h"
class Bullet
{
private:
	bool _isshot;
	bool _isebullet;
	int _x;
	int _y;
public:

	Bullet(int x, int y) {
		_x = x;
		_y = y;
		_isshot = false;
		_isebullet = false;
	}
	static int X(Bullet bullet) { return bullet._x; }
	static int Y(Bullet bullet) { return bullet._y; }
	static bool IsShot(Bullet bullet) { return bullet._isshot; }
	static void FireBullet(Bullet& bullet, Player player);
	static void Draw(Bullet &bullet);
	static void Die(Bullet& bullet);
	static void Collision(Enemy& enemy, Bullet& bullet, Player &player);
	static bool IsEBullet(Bullet bullet) { return bullet._isebullet; }
	static void FireEBullet(Bullet& bullet, Enemy enemy);
	static void EDraw(Bullet& bullet);
};

