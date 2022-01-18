#pragma once
class Player
{
private:
	int _x;
	int _y;
	bool _isdead;
	bool _shielded;

public:
	Player(int x, int y) {
		_x = x;
		_y = y;
		_isdead = false;
		_shielded = false;
	}
	static int X(Player player) { return player._x; }
	static int Y(Player player) { return player._y; }
	static bool IsDead(Player player) { return player._isdead; }
	static bool Shielded(Player player) { return player._shielded; }
	static void Move(Player &player);
	static void Draw(Player player);
	static void Erase(Player player);
	static void LScrollPlayer(Player &player);
	static void RScrollPlayer(Player& player);
};

