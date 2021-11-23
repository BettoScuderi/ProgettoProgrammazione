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

void show_console_cursor(bool show) {
	CONSOLE_CURSOR_INFO ci;
	GetConsoleCursorInfo(gHndConsole, &ci);
	ci.bVisible = show ? TRUE : FALSE;
	SetConsoleCursorInfo(gHndConsole, &ci);
}

void set_console_size(SHORT wConsole, SHORT hConsole) {
	COORD dim = { wConsole, hConsole };
	SMALL_RECT sr = { 0, 0, wConsole, hConsole };
	SetConsoleScreenBufferSize(gHndConsole, dim);
	SetConsoleWindowInfo(gHndConsole, TRUE, &sr);
}

void set_console_color(WORD color) {
	SetConsoleTextAttribute(gHndConsole, color);
}

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

void platform(int x, int y, int z) {
	SHORT a = x;
	for (int i = 0; i < z; i++) {
		gotoxy(a, y); putchar('I');
		a = a + 1;
	}
}

bool salto(SHORT x, SHORT y, int yp, int xp, int zp) {
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

int main() {
	SHORT x = 0;
	SHORT y = H_CONSOLE - 1;
	int o = 18;
	int a = assex();
	int l = assez();

	platform(a, o, l);
	init_console(W_CONSOLE, H_CONSOLE);
	show_char_at(x, y, CHAR_NAVICELLA, 0);

	while (1 != 0) {
		show_console_cursor(false);
		bool jump = salto(x, y, o, a, l);
		bool gravsx = gravitys(x, a);
		bool gravdx = gravityd(x, a, l);
		char tasto = _getch();
		if (tasto == 75 && gravsx){

			x = x - 1 >= 0 ? x - 1 : x;							//sinistra
			y = y + 2 < H_CONSOLE ? y + 2 : y;
			gotoxy(x + 1, y - 2); putchar(' ');

		}
		else if (tasto == 75 && (!gravsx)) {
			
			x = x - 1 >= 0 ? x - 1 : x;							

		}
		else if (tasto == 77 && gravdx) {

			x = x + 1 < W_CONSOLE ? x + 1 : x;                  //destra
			y = y + 2 < H_CONSOLE ? y + 2 : y;
			gotoxy(x - 1, y - 2); putchar(' ');

		}
		else if (tasto == 77 && (!gravdx)) {

			x = x + 1 < W_CONSOLE ? x + 1 : x;

		}
		else if (tasto == 72 && jump) {

			y = y - 2 >= 1 ? y - 2 : y;                         //su 
																
		}
		//*
		else if(tasto == 72 && (!jump)) {					//serve per non far scorrere il terminale

			y = y - 2 >= 1 ? y - 2 : y;
			y = y + 2 < H_CONSOLE ? y + 2 : y;                  

		}
		//*/
		else if (tasto == 80) {

			y = y + 2 < H_CONSOLE ? y + 2 : y;                  //giù

		}

		show_char_at(x, y, CHAR_NAVICELLA, tasto);
	}
}
