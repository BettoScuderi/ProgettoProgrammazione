#pragma once
#include "Player.h"
class Powerup
{
protected:
	int _x;
	int _y;
	bool _isdead;
public:
	Powerup(int x, int y) {
		_x = x;
		_y = y;
		_isdead = false;
	}
	static int X(Powerup powerup) { return powerup._x; }
	static int Y(Powerup powerup) { return powerup._y; }
	static bool IsDead(Powerup powerup) { return powerup._isdead; }
	static bool Collision(Powerup& powerup, Player& player);
	static void Die(Powerup& powerup);
	static void Draw(Powerup powerup);
	static void Bonus(Powerup powerup){}
};

class Shield:public Powerup {
protected:
	wchar_t _charsh;
public:
	Shield(int x, int y) :Powerup(x, y) {
		_charsh = '$';
	}
	static void Draw(Shield shield);
	static void Bonus(Player player) { player._shielded = true; }
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