#pragma once
#include "gioco.h"
#include "Powerup.h"
#include "Enemy.h"
class Platform
{
private:
	int _xinizio;
	int _xfine;
	Powerup _powerup;
	Enemy _enemy;
public:
	int _height;
	bool _todraw;
	Platform(SHORT xinizio, SHORT xfine, SHORT height) {
		_xinizio = xinizio;
		_xfine = xfine;
		_height = height;
		_todraw = false;
		int r = rand() % 10;
		if (r = 0) { _powerup = Shield::Shield(rand() % (_xfine - _xinizio) + _xinizio, _height); }
		else if(r=1){}
		else if (r = 2) {}//...
		r = rand() % 3;
		if (r = 0) { _enemy = Enemy(0, 0, 0); }//.....
		else if (r = 1) {}
		else if (r = 2) {}
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

