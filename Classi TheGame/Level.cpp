#include "Level.h"
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

void platform(int x, int y, int z) {
	SHORT a = x;
	for (int i = 0; i < z; i++) {
		gotoxy(a, y); putchar('I');
		a = a + 1;
	}
}
