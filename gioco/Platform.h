#pragma once
#include "gioco.h"
class Platform
{
private:
	SHORT _xinizio;
	SHORT _xfine;

public:
	SHORT _height;
	bool _todraw;
	Platform(SHORT xinizio, SHORT xfine, SHORT height) {
		_xinizio = xinizio;
		_xfine = xfine;
		_height = height;
		_todraw = false;
	}
	static SHORT Xinizio(Platform platform) { return platform._xinizio; };
	static SHORT Xfine(Platform platform) { return platform._xfine; };
	static SHORT Height(Platform platform) { return platform._height; };
	static bool ToDraw(Platform platform) { return platform._todraw; };
	static void Draw(Platform platform);
	static void Erase(Platform platform);
	static void LScrollPlatform(Platform& platform);
	static void RScrollPlatform(Platform& platform);
};

