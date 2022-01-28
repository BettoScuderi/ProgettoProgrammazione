#pragma once
#include <Windows.h>
#include "Player.h"

#define W_CONSOLE 80	//definire le dimensioni della conosole
#define H_CONSOLE 20    


class gioco
{
public:
	static void gotoxy(int x, int y);
	static void set_console_color(WORD color);
	static char scan_output(SHORT x, SHORT y);
	static void ShowPoints(Player player);
};

