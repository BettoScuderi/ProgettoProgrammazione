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
#include "Level.h"
using namespace std;

HANDLE gHndConsole = GetStdHandle(STD_OUTPUT_HANDLE);

struct lvlbilist {			//bilista di "chunk"
	lvlbilist* prev  =NULL;
	Level lvl= Level::Level(0,0,0);
	lvlbilist* next = NULL;
};
typedef lvlbilist* lvlptr;

char gioco::scan_output(SHORT x, SHORT y) {		//restituisce il carattere presente alle coordinate in input
	LPWSTR buffer = new wchar_t[1];
	DWORD dwChars;
	ReadConsoleOutputCharacterW(gHndConsole, buffer, 1, { x,y }, &dwChars);
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

void gioco::gotoxy(int x, int y) {		//posiziona il cursore alle coordinate in input
	COORD coord = { x, y };
	SetConsoleCursorPosition(gHndConsole, coord);
}

void init_console(int wConsole, int hConsole) {		//inizializza la console
	set_console_size(wConsole, hConsole);
	int a = 0;
	for (int i = 0; i < wConsole; i++) {
		gioco::set_console_color(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE |FOREGROUND_INTENSITY);
		gioco::gotoxy(a, 0); putchar('_');
		gioco::gotoxy(a, hConsole); putchar('T');
		a = a + 1;
	}
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	show_console_cursor(false);
}

void KeepFrame(int wConsole, int hConsole) {		//non fa cancellare la cornice del gioco
	int a = 0;
	for (int i = 0; i < wConsole; i++) {
		gioco::set_console_color(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
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

int bilist_length(lvlptr head) {
	lvlptr totail = head;
	int i = 0;
	while (totail->next != NULL) {
		totail = totail->next;
		i++;
	}
	return i;
}

void Tail_ins(lvlptr &tail, lvlptr head) {		//genera un nuovo livello messo per ultimo e sposta tail in modo da puntare sempre l'utlimo
	lvlptr q;
	int length = bilist_length(head);
	int diff = 0;
	diff = length/8;
	if (diff > 9) {
		diff = 9;
	}
	q = new lvlbilist;
	tail->next = q;
	(q)->lvl = Level::Level(diff, Level::Xfine(tail->lvl)+1, Level::Xfine(tail->lvl) + 10);	//nuovo livello da generare (manca ancora un modo per gestire la difficolta')
	(q)->prev = tail;
	tail = q;
}
void Genero(lvlptr &tail, lvlptr head) {		//fino a quando l'ultimo "chunk" non esce dallo schermo ne genera uno nuovo da mettere in fondo
	while (Level::Xfine(tail->lvl)<80) {
		Tail_ins(tail, head);
	}
}
void KeepFscreenlvl(lvlptr &fscreenlvl) {		//mantiene fscreenlvl a puntare il primo "chunk" dello schermo
	if (Level::Xfine(fscreenlvl->lvl) < 0) {
		fscreenlvl = fscreenlvl->next;
	}
	else if (Level::Xfine(fscreenlvl->lvl) > 9) {
		fscreenlvl = fscreenlvl->prev;
	}
}
void KeepLscreenlvl(lvlptr &lscreenlvl) {		//mantiene lscreenlvl a puntare l'ultimo "chunk" dello schermo
	if (Level::Xfine(lscreenlvl->lvl) < 79) {
		lscreenlvl = lscreenlvl->next;
	}
	else if (Level::Xinizio(lscreenlvl->lvl) > 79) {
		lscreenlvl = lscreenlvl->prev;
	}
}
void LScroll(Player& player, lvlptr head) {		//fa scorrere tutto di uno a sinistra quando il giocatore raggiunge la parte destra dello schermo
	if (Player::X(player) > 55) {
		lvlptr p = head;
		Player::LScrollPlayer(player);
		while (p != NULL) {
			Level::LScrollLevel(p->lvl);
			p = p->next;
		}
	}
}
void RScroll(Player& player, lvlptr head) {				//fa scorrere tutto di uno a destra quando il giocatore raggiunge la parte sinistra dello schermo
	if (Player::X(player) < 23 && Level::Xinizio(head->lvl)<0) {
		lvlptr pt = head;
		Player::RScrollPlayer(player);
		while (pt != NULL) {
			Level::RScrollLevel(pt->lvl);
			pt = pt->next;
		}
	}
}
void UpdateScreenLvl(lvlptr fscreenlvl, lvlptr lscreenlvl, Bullet *bullets[], Player player) {		//aggiorna tutti gli oggetti nello schermo
	lvlptr ptr = fscreenlvl;
	while (ptr != lscreenlvl->next) {			//scorre dal primo "chunk" dello schermo fino all'ultimo
		for (int i = 0; i < 10; i++) {
			if (Platform::ToDraw(*ptr->lvl.platforms[i])) {				//ridisegna ogni piattaforma da disegnare
				Platform::Erase(*ptr->lvl.platforms[i]);
				Platform::Draw(*ptr->lvl.platforms[i]);
			}
		}
		for (int i = 0; i < 10; i++) {		//controlla per ogni nemico se...
			if (Enemy::FireCounter(*ptr->lvl.enemies[i]) == Enemy::FireRate(*ptr->lvl.enemies[i])) {	//il contatore per sparare ha raggiunto il valore per poter sparare
				Enemy::ZeroCounter(*ptr->lvl.enemies[i]);
				for (int j = 0; j < 100; j++) {			//spara il primo proiettile disponibile
					if (!(Bullet::IsShot(*bullets[j]))) {
						Bullet::FireEBullet(*bullets[j], *ptr->lvl.enemies[i]);
						j = 100;
					}
				}
			}
		else { Enemy::Sparerai(*ptr->lvl.enemies[i]); }	//altrimenti aumenta di 1 il contatore per sparare
			if (!(Enemy::IsDead(*ptr->lvl.enemies[i]))) {	//per ogni nemico vivo viene applicata la gravita' e viene disegnato
				Enemy::Move(*ptr->lvl.enemies[i]);
				Enemy::Draw(*ptr->lvl.enemies[i]);
			}
		}
		for (int i = 0; i < 10; i++) {		//per ogni nemico e piattaforma
			for (int j = 0; j < 100; j++) {		//e per ogni proiettile sparato
				if (Bullet::IsShot(*bullets[j])) {
					Bullet::Collision(*ptr->lvl.enemies[i], *bullets[j], player, *ptr->lvl.platforms[i]);		//controlla se un proiettile occupa la stessa posizione di un nemico o del giocatore
				}
			}
		}
		ptr = ptr->next;
	}
}
int main() {
	srand(time(NULL));
	lvlptr head, tail;	//inizializza i primi due puntatori a "chunk"
	head = new lvlbilist;
	head->prev = NULL;
	head->lvl = Level::Level(0, 0, 9); //questo sara' sempre il primo "chunk" e head punta sempre ad esso
	tail = new lvlbilist;
	tail->prev = head;
	tail->next = NULL;
	tail->lvl = Level::Level(0, 10, 19);
	head->next = tail;
	lvlptr first_screen_lvl, last_screen_lvl;	//inizializza i due puntatori che punteranno sempre il primo e l'ultimo "chunk" visibile
	first_screen_lvl = head;
	last_screen_lvl = tail;
	int x = 0;
	int y = H_CONSOLE - 1;
	//int o = 18;
	//int a = assex();
	//int l = assez();
	//platform(a, o, l);
	init_console(W_CONSOLE, H_CONSOLE);
	/*gioco::show_char_at(x, y, CHAR_NAVICELLA);*/
	Bullet *bullets[100];		//dichiara il puntatore ad array di proiettili
	Player player = Player(x, y);		//genera il giocatore
	/*srand((unsigned)time(0));
	Enemy enemy = Enemy(rand() % (W_CONSOLE - 1) + 1, rand() % (H_CONSOLE - 1) + 1, rand() % 20 + 40);*/
	for (int i = 0; i < 100; i++) {		//inizializza tutti i proiettili
		bullets[i] = new Bullet(0, 0);
	}
	while (1 != 0) {	//game loop
		KeepFrame(W_CONSOLE, H_CONSOLE);
		LScroll(player, head);
		RScroll(player, head);
		Genero(tail, head);
		KeepFscreenlvl(first_screen_lvl);
		KeepLscreenlvl(last_screen_lvl);
		UpdateScreenLvl(first_screen_lvl, last_screen_lvl, bullets, player);
		/*if (Enemy::FireCounter(enemy) == Enemy::FireRate(enemy)) {
			Enemy::ZeroCounter(enemy);
			for (int i = 0; i < 100; i++) {
				if (!(Bullet::IsShot(*bullets[i]))) {
					Bullet::FireEBullet(*bullets[i], enemy);
					i = 100;
				}
			}
		}
		else { Enemy::Sparerai(enemy); }*/
		if (GetKeyState(VK_SPACE) < 0) {		//se sto premendo la barra spaziatrice sparo il primo proiettile disponibile
			for (int i = 0; i<100; i ++) {
				if (!(Bullet::IsShot(*bullets[i]))) {
					Bullet::FireBullet(*bullets[i], player);
					i = 100;
				}
			}
		}
		for (int i = 0; i < 100; i++) {		//per ogni proiettile che e' stato sparato aggiorna la loro posizione e li disegna
			if (Bullet::IsShot(*bullets[i])) {
				if (Bullet::IsEBullet(*bullets[i])) {		//controlla se si tratta di proiettili di nemici o del giocatore
					Bullet::EDraw(*bullets[i]);
				}
				else {
					Bullet::Draw(*bullets[i]);
				}
			}
		}
		show_console_cursor(false);
		/*bool jump = salto(x, y, o, a, l);
		bool gravsx = gravitys(x, a);
		bool gravdx = gravityd(x, a, l);
		bool salto_vuoto = false;*/
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
		/*for (int i = 0; i < 100; i++) {
			if (Bullet::IsShot(*bullets[i])) {
				Bullet::Collision(enemy, *bullets[i], player);
			}
		}*/
		/*if (!(Enemy::IsDead(enemy))) {
			Enemy::Move(enemy);
			Enemy::Draw(enemy);
		}*/
		if (!(Player::IsDead(player))) {		//aggiorna la posizione del giocatore e lo disegna
			Player::Erase(player);
			Player::Move(player);
			Player::Draw(player);
		}
		Sleep(50);
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