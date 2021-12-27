// gioco.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//
#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "gioco.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
using namespace std;

HANDLE gHndConsole = GetStdHandle(STD_OUTPUT_HANDLE);

char gioco::scan_output(short x, short y) {
	LPWSTR buffer = new wchar_t[1];
	DWORD dwChars;
	ReadConsoleOutputCharacter(gHndConsole, buffer, 1, { x,y }, &dwChars);
	char mio = *buffer;
	return mio;
}
void show_console_cursor(bool show) {
	CONSOLE_CURSOR_INFO ci;
	GetConsoleCursorInfo(gHndConsole, &ci);
	ci.bVisible = show ? TRUE : FALSE;
	SetConsoleCursorInfo(gHndConsole, &ci);
}

void set_console_size(int wConsole, int hConsole) {
	COORD dim = { wConsole, hConsole };
	SMALL_RECT sr = { 0, 0, wConsole, hConsole };
	SetConsoleScreenBufferSize(gHndConsole, dim);
	SetConsoleWindowInfo(gHndConsole, TRUE, &sr);
}

void gioco::set_console_color(WORD color) {
	SetConsoleTextAttribute(gHndConsole, color);
}

void gioco::gotoxy(int x, int y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(gHndConsole, coord);
}

void init_console(int wConsole, int hConsole) {
	set_console_size(wConsole, hConsole);
	int a = 0;
	for (int i = 0; i < wConsole; i++) {
		gioco::gotoxy(a, 0); putchar('_');
		gioco::gotoxy(a, hConsole); putchar('T');
		a = a + 1;
	}
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	show_console_cursor(false);
}

void platform(int x, int y, int z) {
	int a = x;
	for (int i = 0; i < z; i++) {
		gioco::gotoxy(a, y); putchar('I');
		a = a + 1;
	}
}

bool salto(int x, int y, int yp, int xp, int zp) {
	if ((y - yp == 1) && (xp <= x) && (x <= xp + zp - 1)) {
		return true;
	}
	else {
		return false;
	}
}

bool gravitys(int x, int xp) {
	if (x < xp + 1) {
		return true;
	}
	else {
		return false;
	}
}

bool gravityd(int x, int xp, int zp) {
	if (x > xp + zp - 2) {
		return true;
	}
	else {
		return false;
	}
}

void gioco::show_char_at(int x, int y, wchar_t c) {
	if (GetKeyState(VK_LEFT) < 0) {
		gioco::gotoxy(x + 1, y); putchar(' ');
	}
	else if (GetKeyState(VK_RIGHT)<0) {
		gioco::gotoxy(x - 1, y); putchar(' ');
	}

	else if (GetKeyState(VK_UP)<0 && (y+2)<H_CONSOLE) {
		gioco::gotoxy(x, y + 2); putchar(' ');
	}
	else if (GetKeyState(VK_DOWN) < 0) {
		gioco::gotoxy(x, y - 2); putchar(' ');
	}
	gioco::gotoxy(x, y);     putwchar(c);
}

int assey() {
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
	int x = 0;
	int y = H_CONSOLE - 1;
	int o = 18;
	int a = assex();
	int l = assez();
	platform(a, o, l);
	init_console(W_CONSOLE, H_CONSOLE);
	/*gioco::show_char_at(x, y, CHAR_NAVICELLA);*/
	Bullet *bullets[100];
	Player player = Player(x, y);
	srand((unsigned)time(0));
	Enemy enemy = Enemy(rand() % (W_CONSOLE-1) + 1, rand() % (H_CONSOLE-1)+1 ,rand() % 20+40);
	for (int i = 0; i < 100; i++) {
		bullets[i] = new Bullet(0, 0);
	}
	while (1 != 0) {
		if (Enemy::FireCounter(enemy) == Enemy::FireRate(enemy)) {
			Enemy::ZeroCounter(enemy);
			for (int i = 0; i < 100; i++) {
				if (!(Bullet::IsShot(*bullets[i]))) {
					Bullet::FireEBullet(*bullets[i], enemy);
					i = 100;
				}
			}
		}
		else { Enemy::Sparerai(enemy); }
		if (GetKeyState(VK_SPACE) < 0) {
			for (int i = 0; i<100; i++) {
				if (!(Bullet::IsShot(*bullets[i]))) {
					Bullet::FireBullet(*bullets[i], player);
					i = 100;
				}
			}
		}
		for (int i = 0; i < 100; i++) {
			if (Bullet::IsShot(*bullets[i])) {
				if (Bullet::IsEBullet(*bullets[i])) {
					Bullet::EDraw(*bullets[i]);
				}
				else {
					Bullet::Draw(*bullets[i]);
				}
			}
		}
		show_console_cursor(false);
		bool jump = salto(x, y, o, a, l);
		bool gravsx = gravitys(x, a);
		bool gravdx = gravityd(x, a, l);
		bool salto_vuoto = false;
		/*
		if (GetKeyState(VK_LEFT)<0 && gravsx) {

			x = x - 1 >= 0 ? x - 1 : x;							//sinistra
			y = y + 2 < H_CONSOLE ? y + 2 : y;
			gioco::gotoxy(x + 1, y - 2); putchar(' ');
			gioco::show_char_at(x, y, CHAR_NAVICELLA);

		}
		else if (GetKeyState(VK_LEFT)<0 && (!gravsx)) {

			x = x - 1 >= 0 ? x - 1 : x;
			gioco::show_char_at(x, y, CHAR_NAVICELLA);

		}
		else if (GetKeyState(VK_RIGHT)<0 && gravdx) {

			x = x + 1 < W_CONSOLE ? x + 1 : x;                  //destra
			y = y + 2 < H_CONSOLE ? y + 2 : y;
			gioco::gotoxy(x - 1, y - 2); putchar(' ');
			gioco::show_char_at(x, y, CHAR_NAVICELLA);

		}
		else if (GetKeyState(VK_RIGHT)<0 && (!gravdx)) {

			x = x + 1 < W_CONSOLE ? x + 1 : x;
			gioco::show_char_at(x, y, CHAR_NAVICELLA);

		}
		else if (GetKeyState(VK_UP)<0 && jump) {

			y = y - 2 >= 1 ? y - 2 : y;
			gioco::show_char_at(x, y, CHAR_NAVICELLA);//su 

		}
		else if (GetKeyState(VK_DOWN)<0) {

			y = y + 2 < H_CONSOLE ? y + 2 : y;
			gioco::show_char_at(x, y, CHAR_NAVICELLA);		//giù

		}
		*/
		for (int i = 0; i < 100; i++) {
			if (Bullet::IsShot(*bullets[i])) {
				Bullet::Collision(enemy, *bullets[i], player);
			}
		}
		if (!(Enemy::IsDead(enemy))) {
			Enemy::Move(enemy);
			Enemy::Draw(enemy);
		}
		if (!(Player::IsDead(player))) {
			Player::Erase(player);
			Player::Move(player);
			Player::Draw(player);
		}
		Sleep(30);
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