#include "GameSystem.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include<windows.h>
#include<conio.h>


using namespace std;

#define W_CONSOLE 83
#define H_CONSOLE 20
#define CHAR_NAVICELLA L'\028'

HANDLE gHndConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoxy(SHORT x, SHORT y) {                                     
	COORD coord = { x, y };
	SetConsoleCursorPosition(gHndConsole, coord);
}

void init_console(SHORT wConsole, SHORT hConsole) {                 
	set_console_size(wConsole, hConsole);
	SHORT a = 0;
	for (int i = 0; i < wConsole; i++) {
		gotoxy(a, 0); putchar('_');
		gotoxy(a, hConsole); putchar('T');
		a = a + 1;
	}
	set_console_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	show_console_cursor(false);
}
5bool salto(SHORT x, SHORT y, int yp, int xp, int zp) {
	if ((y - yp == 1) && (xp <= x) && (x <= xp + zp - 1)) {
		return true;
	}
	else {
		return false;
	}
}

bool gravitys(SHORT x, int xp) {
	if (x < xp + 1) {
		return true;
	}
	else {
		return false;
	}
}

bool gravityd(SHORT x, int xp, int zp) {
	if (x > xp + zp -2) {
		return true;
	}
	else {
		return false;
	}
}

void show_char_at(SHORT x, SHORT y, wchar_t c, char tasto) {
	if (tasto == 77) {
		gotoxy(x - 1, y); putchar(' ');
	}
	else if (tasto == 75) {
		gotoxy(x + 1, y); putchar(' ');
	}
	else if (tasto == 80) {
		gotoxy(x, y - 2); putchar(' ');
	}
	else if (tasto == 72) {
		gotoxy(x, y + 2); putchar(' ');
	}
	gotoxy(x, y);     putwchar(c);
}

int assey(){
    srand((unsigned)time(0));
    int i;
    i = (rand() % 18) + 1;
    if (i % 2 != 0) {
        i++;
    }
    return i;
}

int assex() {
    srand((unsigned)time(0));
    int j;
    j = (rand() % 80) + 1;
    return j;
}

int assez() {
    srand((unsigned)time(0));
    int z;
    z = (rand() % 8) + 4;
    return z;
}


GameSystem::GameSystem() {
  
  
}
