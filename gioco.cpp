// gioco.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;
#define W_CONSOLE       100
#define H_CONSOLE       15
#define CHAR_NAVICELLA  'O'

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
        gotoxy(a, 0); putchar('Q');
        gotoxy(a, hConsole); putchar('Q');
        a=a+1;
    }
    set_console_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    show_console_cursor(false);
}

void show_char_at(SHORT x, SHORT y, char c) {
    gotoxy(x, y);     putchar (c);
    gotoxy(x - 1, y); putchar(' ');
    gotoxy(x + 1, y); putchar(' ');
    gotoxy(x, y - 1); putchar(' ');
    gotoxy(x, y + 1); putchar(' ');
}

int main() {
    SHORT x = W_CONSOLE / 2;
    SHORT y = H_CONSOLE - 1;

    init_console(W_CONSOLE, H_CONSOLE);
    show_char_at(x, y, CHAR_NAVICELLA);

    while (1 != 0) {
        show_console_cursor(false);
        char tasto = _getch();

        switch (tasto) {
        case 75: x = x - 1 >= 0 ? x - 1 : x; break;
        case 77: x = x + 1 < W_CONSOLE ? x + 1 : x; break;
        case 72: y = y - 1 >= 1 ? y - 1 : y; break;
        case 80: y = y + 1 < H_CONSOLE ? y + 1 : y; break;
        default:;
        }

        show_char_at(x, y, CHAR_NAVICELLA);
    }
}

// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug

// Suggerimenti per iniziare: 
//   1. Usare la finestra Esplora soluzioni per aggiungere/gestire i file
//   2. Usare la finestra Team Explorer per connettersi al controllo del codice sorgente
//   3. Usare la finestra di output per visualizzare l'output di compilazione e altri messaggi
//   4. Usare la finestra Elenco errori per visualizzare gli errori
//   5. Passare a Progetto > Aggiungi nuovo elemento per creare nuovi file di codice oppure a Progetto > Aggiungi elemento esistente per aggiungere file di codice esistenti al progetto
//   6. Per aprire di nuovo questo progetto in futuro, passare a File > Apri > Progetto e selezionare il file con estensione sln
