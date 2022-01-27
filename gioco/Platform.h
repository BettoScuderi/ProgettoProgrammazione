#pragma once
#include "gioco.h"
#include "Powerup.h"
#include "Enemy.h"
class Platform
{
private:
	int _xinizio;
	int _xfine;
public:
	Powerup* _powerup;
	Enemy* _enemy;
	int _height;
	bool _todraw;
	Platform(SHORT xinizio, SHORT xfine, SHORT height) {
		_xinizio = xinizio;
		_xfine = xfine;
		_height = height;
		_todraw = true;
		//_enemy = new Enemy(-999, 0);
		//_powerup = new Powerup(0, 0);
		int r = rand() % 100;
		if (r>=0&&r<2) { _powerup = new Shield(rand() % (_xfine - _xinizio) + _xinizio, _height-1); }
		else if (r >= 2&&r<4) { _powerup = new Ratio(rand() % (_xfine - _xinizio) + _xinizio, _height-1); }
		else if (r >= 4&&r<6) { _powerup = new Star(rand() % (_xfine - _xinizio) + _xinizio, _height-1); }
		else if (r >= 6&&r<8) { _powerup = new Heart(rand() % (_xfine - _xinizio) + _xinizio, _height-1); }
		else if (r ==8) { _powerup = new Nuke(rand() % (_xfine - _xinizio) + _xinizio, _height -1); }
		else { _powerup = new Powerup(-999, 0); Powerup::Die(*_powerup); };
		r = rand() % 60;
		if (r >= 0 && r<5) { _enemy = new Shooter(rand() % (_xfine - _xinizio) + (_xinizio+1), _height-1, rand() % 80 + 20); }
		else if (r>=5 && r < 15) { _enemy = new Spiky(rand() % (_xfine - _xinizio) + (_xinizio+1), _height-1);}
		else if (r>=15 && r < 25) { _enemy = new Shieldy(rand() % (_xfine - _xinizio) + (_xinizio+1), _height-1);}
		else if (r>=25 && r < 45) { _enemy = new Invincible(_xfine - ((_xfine - _xinizio) / 2), H_CONSOLE - 5); }
		else{ _enemy = new Enemy(-999, 0); Enemy::Die(*_enemy); }
	}
	static int Xinizio(Platform platform) { return platform._xinizio; };
	static int Xfine(Platform platform) { return platform._xfine; };
	static int Height(Platform platform) { return platform._height; };
	static bool ToDraw(Platform platform) { return platform._todraw; };
	static void Draw(Platform platform);
	static void Erase(Platform platform);
	static void LScrollPlatform(Platform& platform);
	static void RScrollPlatform(Platform& platform);
};

