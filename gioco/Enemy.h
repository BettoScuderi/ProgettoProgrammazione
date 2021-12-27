#pragma once
class Enemy
{
private:
	int _x;
	int _y;
	bool _isdead;
	int _firerate;
	int _firecounter;
public:
	Enemy(int x, int y, int firerate) {
		_x = x;
		_y = y;
		_isdead = false;
		_firerate = firerate;
		_firecounter = 0;
	}
	static int X(Enemy enemy) { return enemy._x; }
	static int Y(Enemy enemy) { return enemy._y; }
	static bool IsDead(Enemy enemy) { return enemy._isdead; }
	static int FireRate(Enemy enemy) { return enemy._firerate; }
	static int FireCounter(Enemy enemy) { return enemy._firecounter; }
	static void Draw(Enemy &enemy);
	static void Move(Enemy &enemy);
	static void Die(Enemy &enemy);
	static void Sparerai(Enemy &enemy);
	static void ZeroCounter(Enemy& enemy) { enemy._firecounter = 0; }
};

