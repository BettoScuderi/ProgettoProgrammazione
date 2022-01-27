#pragma once
class Player
{
private:
	int _x;
	int _y;
	bool _isdead;
	int _firecounter;
	int _kcounter;
	int _lives;
public:
	bool _shielded;
	int _shieldcounter;
	int _fireratio;
	bool _killable;
	bool _nuke;
	char _charpl;
	int _points;
	Player(int x, int y) {
		_x = x;
		_y = y;
		_isdead = false;
		_shielded = false;
		_shieldcounter = 5;
		_fireratio = 19;
		_firecounter = 19;
		_killable = true;
		_nuke = false;
		_charpl = 2;
		_kcounter = 0;
		_lives = 3;
		_points = 0;
	}
	static int X(Player player) { return player._x; }
	static int Y(Player player) { return player._y; }
	static bool IsDead(Player player) { return player._isdead; }
	static bool Shielded(Player player) { return player._shielded; }
	static int FireCounter(Player player) { return player._firecounter; }
	static int FireRatio(Player player) { return player._fireratio; }
	static bool Killable(Player player) { return player._killable; }
	static bool Nuke(Player player) { return player._nuke; }
	static char CharPl(Player player) { return player._charpl; }
	static int KCounter(Player player) { return player._kcounter; }
	static int Lives(Player player) { return player._lives; }
	static void Move(Player &player);
	static void Draw(Player player);
	static void Erase(Player player);
	static void SetFireCounter(Player& player) { player._firecounter = player._fireratio; }
	static void ReduceFireCounter(Player& player) { player._firecounter--; }
	static void SetKCounter(Player& player, int kcounter) { player._kcounter = kcounter;	player._killable = false; player._charpl = 1;}
	static void ReduceKCounter(Player& player) { player._kcounter--; if (player._kcounter == 0) { player._killable = true; player._charpl = 2; } }
	static void OneUp(Player& player);
	static void OneDown(Player& player);
	static void LScrollPlayer(Player &player);
	static void RScrollPlayer(Player& player);
};

