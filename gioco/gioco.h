#pragma once
#include <Windows.h>

#define W_CONSOLE 80
#define H_CONSOLE 20
#define CHAR_NAVICELLA L'\2'
class gioco
{
public:
	static void show_char_at(int x, int y, wchar_t c);
	static void gotoxy(int x, int y);
	static void set_console_color(WORD color);
	static char scan_output(SHORT x, SHORT y);
};

