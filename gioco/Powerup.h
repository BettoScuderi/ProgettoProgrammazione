#pragma once
#include "Player.h"
class Powerup
{
protected:
	int _x;
	int _y;
	bool _isdead;
	wchar_t _char;
public:
	int _bonus;
	Powerup(int x, int y) {
		_x = x;
		_y = y;
		_isdead = false;
		_char = 'F';
		_bonus = 0;
	}
	static int X(Powerup powerup) { return powerup._x; }
	static int Y(Powerup powerup) { return powerup._y; }
	static bool IsDead(Powerup powerup) { return powerup._isdead; }
	static void Collision(Powerup& powerup, Player& player);
	static void Die(Powerup& powerup);
	static void Draw(Powerup powerup);
	static void Erase(Powerup powerup);
	static void Bonus(Powerup& powerup, Player& player);
	static void RScrollPowerup(Powerup& powerup);
	static void LScrollPowerup(Powerup& powerup);
};

class Shield:public Powerup {
public:
	Shield(int x, int y) :Powerup(x, y) {
		_char = 185;
		_bonus = 1;
	}
	static void Draw(Shield shield);
	static void Collision(Shield& shield, Player& player);
	static void Bonus(Player& player) { player._shielded = true; }
};

class Ratio:public Powerup {
public:
	Ratio(int x, int y) :Powerup(x, y) {
		_char = 175;
		_bonus = 2;
	}
	static void Draw(Ratio ratio);
	static void Collision(Ratio& ratio, Player& player);
	static void Bonus(Player& player);
};

class Star :public Powerup {
public:
	Star(int x, int y) :Powerup(x, y) {
		_char = 42;
		_bonus = 3;
	}
	static void Draw(Star star);
	static void Collision(Star& star, Player& player);
	static void Bonus(Player& player);
};

class Heart :public Powerup {
public:
	Heart(int x, int y) :Powerup(x, y) {
		_char = 3;
		_bonus = 4;
	}
	static void Draw(Heart heart);
	static void Collision(Heart& heart, Player& player);
	static void Bonus(Player& player);
};

class Nuke :public Powerup {
public:
	Nuke(int x, int y) :Powerup(x, y) {
		_char = 176;
		_bonus = 5;
	}
	static void Draw(Nuke nuke);
	static void Collision(Nuke& nuke, Player& player);
	static void Bonus(Player& player) { player._nuke = true; };
};
/*
NEMICI
		L '\x1e'
L '\x111' 0 L'\x110'

POWER UP
* Stella di Super Mario
@ Ricarica proiettili/aumento cadenza proiettili
$ scudo
L'\3' punti/vita
8 killa tutti nemici visibili
*/