// gioco.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;
#define W_CONSOLE       83
#define H_CONSOLE       20
#define CHAR_NAVICELLA  L'\028'
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
        gotoxy(a, hConsole); putchar('_');
        a=a+1;
    }
    set_console_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    show_console_cursor(false);
}
/*
void show_char_at(SHORT x, SHORT y, char c) {
    gotoxy(x, y);     putchar(c);
    gotoxy(x - 1, y); putchar(' ');
    gotoxy(x + 1, y); putchar(' ');
    gotoxy(x, y - 1); putchar(' ');
    gotoxy(x, y + 1); putchar(' ');
}
*/
void show_char_at(SHORT x, SHORT y, wchar_t c, char tasto) {
    if (tasto == 77) {
        gotoxy(x - 1, y); putchar(' ');
    }
    else if(tasto == 75){
        gotoxy(x+1, y); putchar(' ');
    }
    else if (tasto == 80) {
        gotoxy(x, y - 1); putchar(' ');
    }
    else if (tasto == 72) {
        gotoxy(x, y + 1); putchar(' ');
    }
    gotoxy(x, y);     putwchar(c);
}
int main() {
    SHORT x = W_CONSOLE / 2;
    SHORT y = H_CONSOLE - 1;

    init_console(W_CONSOLE, H_CONSOLE);
    show_char_at(x, y, CHAR_NAVICELLA, 0);

    while (1 != 0) {
        show_console_cursor(false);
        char tasto = _getch();
        if (tasto == 75)
        {
            x = x - 1 >= 0 ? x - 1 : x;                         //sinistra
        }
        else if (tasto == 77) {

            x = x + 1 < W_CONSOLE ? x + 1 : x;                  //destra

        }
        else if (tasto == 72) {

            y = y - 1 >= 1 ? y - 1 : y;                         //su

        }
        else if (tasto == 80) {

            y = y + 1 < H_CONSOLE ? y + 1 : y;                  //giù

        }

        show_char_at(x, y, CHAR_NAVICELLA, tasto);
    }
}

