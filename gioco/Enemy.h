#pragma once
#include "Player.h"
class Enemy
{
protected:
	int _x;
	int _y;
	bool _isdead;
	int _firerate;
	int _firecounter;
	char _char;
	bool _shootable;
	bool _spiky;
public:
	Enemy(int x, int y) {
		_x = x;
		_y = y;
		_isdead = false;
		_shootable = true;
		_spiky = false;
		_firecounter = 0;
		_firerate = -1;
		_char = 'E';
	}
	static int X(Enemy enemy) { return enemy._x; }
	static int Y(Enemy enemy) { return enemy._y; }
	static bool IsDead(Enemy enemy) { return enemy._isdead; }
	static bool Shootable(Enemy enemy) { return enemy._shootable; }
	static bool Spiky(Enemy enemy) { return enemy._spiky; }
	static int FireRate(Enemy enemy) { return enemy._firerate; }
	static int FireCounter(Enemy enemy) { return enemy._firecounter; }
	static void ZeroCounter(Enemy& enemy) { enemy._firecounter = 0; }		//azzera il contatore per sparare
	static void Sparerai(Enemy& enemy);
	static void Draw(Enemy &enemy);
	static void Erase(Enemy& enemy);
	static void Die(Enemy &enemy);
	static void Collision(Enemy& enemy, Player& player);
	static void LScrollEnemy(Enemy& enemy);
	static void RScrollEnemy(Enemy& enemy);
};

class Shooty :public Enemy {		//nemico che spara
public:
	Shooty(int x, int y, int firerate) :Enemy(x, y) {
		_firerate = firerate;
		_char = 2;
	}
};

class Spiky :public Enemy {		//nemico spinoso
public:
	Spiky(int x, int y) :Enemy(x, y) {
		_char = 15;
		_spiky = true;
	}
};

class Shieldy :public Enemy {		//nemico con scudo
public:
	Shieldy(int x, int y) :Enemy(x, y) {
		_char = 232;
		_shootable = false;
	}
};

class Floory :public Enemy {		//nemico invincibile
public:
	Floory(int x, int y) :Enemy(x, y) {
		_char = 30;
		_shootable = false;
		_spiky = true;
	}
};