// gioco.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//
#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "gioco.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Level.h"
#include "Powerup.h"
using namespace std;

HANDLE gHndConsole = GetStdHandle(STD_OUTPUT_HANDLE);

struct lvlbilist {			//bilista di "chunk"
	lvlbilist* prev  =NULL;
	Level lvl= Level::Level(0,0,0);
	lvlbilist* next = NULL;
};
typedef lvlbilist* lvlptr;
void GameMenu();
void Tutorial();
void GameLoop();
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
	SMALL_RECT sr = { 0, 0, wConsole, hConsole};
	SetConsoleScreenBufferSize(gHndConsole, dim);
	SetConsoleWindowInfo(gHndConsole, TRUE, &sr);
}

void gioco::set_console_color(WORD color) {
	SetConsoleTextAttribute(gHndConsole, color);
}

void gioco::gotoxy(int x, int y) {		//posiziona il cursore alle coordinate in input
	if (x >= 0 && x <= W_CONSOLE && y >= 0 && y <= H_CONSOLE) {
		COORD coord = { x, y };
		SetConsoleCursorPosition(gHndConsole, coord);
	}
}
void GameOver(Player player);
void init_console(int wConsole, int hConsole, Player& player) {		//inizializza la console
	int a = 0;
	for (int i = 0; i <= wConsole; i++) {
		gioco::set_console_color(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		gioco::gotoxy(a, 0); putchar(219);
		gioco::set_console_color(FOREGROUND_GREEN | BACKGROUND_GREEN);
		gioco::gotoxy(a, (hConsole-4)); putchar(219);
		a = a + 1;
	}
	gioco::set_console_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	gioco::gotoxy(W_CONSOLE - 12, H_CONSOLE - 2);
	cout << "DIFFICOLTA':";
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
	for (int i = 0; i < Player::Lives(player); i++) {
		gioco::gotoxy(i, H_CONSOLE - 3);
		putchar(3);
	}
	gioco::set_console_color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	gioco::gotoxy(0, H_CONSOLE - 1);
	cout << "PUNTEGGIO:";
	gioco::ShowPoints(player);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	show_console_cursor(false);
}

/*void KeepFrame(int wConsole, int hConsole) {		//non fa cancellare la cornice del gioco
	int a = 0;
	for (int i = 0; i < wConsole; i++) {
		gioco::set_console_color(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		gioco::gotoxy(a, 0); putchar(219);
		gioco::set_console_color(FOREGROUND_GREEN | BACKGROUND_GREEN);
		gioco::gotoxy(a, hConsole); putchar(219);
		a = a + 1;
	}
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	show_console_cursor(false);
}*/

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

void Tutorial() {
	system("cls");
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "COMANDI:"; 
	gioco::gotoxy(W_CONSOLE - 28, 0);	
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Premi Q per tornare al menu'"  << "\n" << "\n";
		gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "W per andare sulla prima piattaforma sopra il giocatore\n";
	cout << "A per spostare il giocatore a sinistra\n";
	cout << "S per andare sulla prima piattaforma sotto il giocatore (o per terra)\n";
	cout << "D per spostare il giocatore a destra\n";
	cout << "Barra spaziatrice per sparare un proiettile\n";
	cout << "Shift sinistro per usare lo scudo anti-proiettile (quando disponibile)\n";
	cout << "\nNEMICI E POWERUP:\n" << "\n";
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_INTENSITY); putchar(2);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "<--Nemico che spara un proiettile ogni tanto\n";
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_INTENSITY); putchar(15);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "<--Nemico che ferisce al contatto e eliminabile solo con proiettili\n";
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_INTENSITY); putchar(232);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "<--Nemico con scudo anti-proiettile\n";
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_INTENSITY); putchar(30);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "<--Nemico invincibile che danneggia al contatto\n\n";
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); putchar(185);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "<--Powerup che rende utilizzabile lo scudo per parare 5 proiettili\n";
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); putchar(175);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "<--Powerup che aumenta la cadenza di fuoco\n";
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); putchar(42);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "<--Powerup che rende invincibili per un po' di tempo\n";
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); putchar(3);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "<--Powerup che aumenta di uno le vite\n";
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); putchar(176);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "<--Powerup che uccide tutti i nemici visibili";
	while (1 != 0) {
		char back = _getch();
		if (back == 'q' || back == 'Q') {
			system("cls");
			GameMenu();
		}
	}
}

void GameMenu() {
	show_console_cursor(false);
	SetConsoleTitleW(L"ThaGame");
	set_console_size(W_CONSOLE, H_CONSOLE);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	gioco::gotoxy((W_CONSOLE/2)-4, ((H_CONSOLE/2)-2));
	cout << "1-PLAY\n";
	gioco::gotoxy((W_CONSOLE / 2) - 6, (H_CONSOLE / 2));
	cout << "2-TUTORIAL\n";
	gioco::gotoxy((W_CONSOLE / 2) - 4, ((H_CONSOLE / 2) + 2));
	cout << "3-EXIT\n";
	while (1 != 0) {
		char sel;
		sel = _getch();
		if (sel == '1') {
			system("cls");
			GameLoop();
		}
		else if (sel == '2') {
			Tutorial();
		}
		else if (sel == '3') {
			system("cls");
			gioco::gotoxy((W_CONSOLE / 2) - 27, (H_CONSOLE / 2));
			cout << "  A  "; Sleep(50);
			cout << "  R  "; Sleep(50);
			cout << "  R  "; Sleep(50);
			cout << "  I  "; Sleep(50);
			cout << "  V  "; Sleep(50);
			cout << "  E  "; Sleep(50);
			cout << "  D  "; Sleep(50);
			cout << "  E  "; Sleep(50);
			cout << "  R  "; Sleep(50);
			cout << "  C  "; Sleep(50);
			cout << "  I  "; Sleep(1000);
			exit(0);
		}
	}
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
	(q)->lvl = Level::Level(diff, Level::Xfine(tail->lvl)+1, Level::Xfine(tail->lvl) + 10);	//nuovo livello da generare
	(q)->prev = tail;
	tail = q;
}
void Genero(lvlptr &tail, lvlptr head) {		//fino a quando l'ultimo "chunk" non esce dallo schermo ne genera uno nuovo da mettere in fondo
	while (Level::Xfine(tail->lvl)<W_CONSOLE) {
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
	if (Level::Xfine(lscreenlvl->lvl) < W_CONSOLE) {	//-1?
		lscreenlvl = lscreenlvl->next;
	}
	else if (Level::Xinizio(lscreenlvl->lvl) > W_CONSOLE) {	//-1?
		lscreenlvl = lscreenlvl->prev;
	}
}
void LScroll(Player& player, lvlptr head) {		//fa scorrere tutto di uno a sinistra quando il giocatore raggiunge la parte destra dello schermo
	if (Player::X(player) > (W_CONSOLE*2/3)) {
		lvlptr p = head;
		Player::LScrollPlayer(player);
		while (p != NULL) {
			Level::LScrollLevel(p->lvl);
			p = p->next;
		}
	}
}
void RScroll(Player& player, lvlptr head) {				//fa scorrere tutto di uno a destra quando il giocatore raggiunge la parte sinistra dello schermo
	if (Player::X(player) < (W_CONSOLE/3) && Level::Xinizio(head->lvl)<0) {
		lvlptr pt = head;
		Player::RScrollPlayer(player);
		while (pt != NULL) {
			Level::RScrollLevel(pt->lvl);
			pt = pt->next;
		}
	}
}
void ShowDifficulty(lvlptr head) {
	int diff = (bilist_length(head)/8);
	if (diff > 9) {
		diff = 9;
	}
	gioco::set_console_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	gioco::gotoxy(W_CONSOLE, (H_CONSOLE - 2));
	putchar(diff+48);
}
void gioco::ShowPoints(Player player) {
	gioco::set_console_color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	for (int i = 10; i <= W_CONSOLE; i++) {
		gioco::gotoxy(i, H_CONSOLE - 1);
		putchar(' ');
	}
	gioco::gotoxy(10, H_CONSOLE - 1);
	cout << player._points;
}
void UpdateScreenLvl(lvlptr fscreenlvl, lvlptr lscreenlvl, Bullet *bullets[], Player& player) {		//aggiorna tutti gli oggetti nello schermo
	lvlptr ptr = fscreenlvl;
	while (ptr != lscreenlvl->next) {		//scorre dal primo "chunk" dello schermo fino all'ultimo
		if (Player::Nuke(player)&&ptr==fscreenlvl) {
			lvlptr lptr = fscreenlvl;
			while (lptr != lscreenlvl->next) {
/*				for (int j = 0; j < 10; j++) {
					if (Platform::ToDraw(*lptr->lvl.platforms[j])) {
						if (!(Enemy::IsDead(*lptr->lvl.platforms[j]->_enemy))) {
							if (Enemy::X(*lptr->lvl.platforms[j]->_enemy) < W_CONSOLE && Enemy::Y(*lptr->lvl.platforms[j]->_enemy)<H_CONSOLE-4) {
								gioco::set_console_color(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
								gioco::gotoxy(Enemy::X(*lptr->lvl.platforms[j]->_enemy), Enemy::Y(*lptr->lvl.platforms[j]->_enemy));
								putchar(176);
								gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
								Sleep(200);
							}
						}
					}
				}*/
				for (int j = 0; j < 10; j++) {
					if (Platform::ToDraw(*lptr->lvl.platforms[j])) {
						if (Enemy::X(*lptr->lvl.platforms[j]->_enemy) <= W_CONSOLE) {
							Enemy::Die(*lptr->lvl.platforms[j]->_enemy);
						}
					}
				}
				lptr = lptr->next;
			}
			player._nuke = false;
		}
		for (int i = 0; i < 10; i++) {
			if (Platform::ToDraw(*ptr->lvl.platforms[i])) {				//ridisegna ogni piattaforma da disegnare
				Platform::Erase(*ptr->lvl.platforms[i]);
				Platform::Draw(*ptr->lvl.platforms[i]);
				Powerup::Erase(*ptr->lvl.platforms[i]->_powerup);
				Powerup::Draw(*ptr->lvl.platforms[i]->_powerup);
				Powerup::Collision(*ptr->lvl.platforms[i]->_powerup, player);
				Enemy::Collision(*ptr->lvl.platforms[i]->_enemy, player);
				if (Enemy::FireCounter(*ptr->lvl.platforms[i]->_enemy) == Enemy::FireRate(*ptr->lvl.platforms[i]->_enemy)) {	//il contatore per sparare ha raggiunto il valore per poter sparare
					Enemy::ZeroCounter(*ptr->lvl.platforms[i]->_enemy);
					for (int j = 0; j < 100; j++) {			//spara il primo proiettile disponibile
						if (!(Bullet::IsShot(*bullets[j]))) {
							Bullet::FireEBullet(*bullets[j], *ptr->lvl.platforms[i]->_enemy);
							j = 100;
						}

					}
				}
				else { Enemy::Sparerai(*ptr->lvl.platforms[i]->_enemy); }	//altrimenti aumenta di 1 il contatore per sparare
				if (!(Enemy::IsDead(*ptr->lvl.platforms[i]->_enemy))) {	//per ogni nemico vivo viene applicata la gravita' e viene disegnato
					//Enemy::Move(*ptr->lvl.platforms[i]->_enemy);
					Enemy::Draw(*ptr->lvl.platforms[i]->_enemy);
				}
			}
		}
		for (int i = 0; i < 10; i++) {		//per ogni nemico e piattaforma
			for (int j = 0; j < 100; j++) {		//e per ogni proiettile sparato
				if (Bullet::IsShot(*bullets[j])) {
					Bullet::Collision(*ptr->lvl.platforms[i]->_enemy, *bullets[j], player, *ptr->lvl.platforms[i]);		//controlla se un proiettile occupa la stessa posizione di un nemico o del giocatore
				}
			}
		}
		ptr = ptr->next;
	}
}
void GameLoop() {
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
	int y = H_CONSOLE - 5;
	//int o = 18;
	//int a = assex();
	//int l = assez();
	//platform(a, o, l);
	/*gioco::show_char_at(x, y, CHAR_NAVICELLA);*/
	Bullet *bullets[100];		//dichiara il puntatore ad array di proiettili
	Player player = Player(x, y);		//genera il giocatore
	init_console(W_CONSOLE, H_CONSOLE, player);
	/*srand((unsigned)time(0));
	Enemy enemy = Enemy(rand() % (W_CONSOLE - 1) + 1, rand() % (H_CONSOLE - 1) + 1, rand() % 20 + 40);*/
	for (int i = 0; i < 100; i++) {		//inizializza tutti i proiettili
		bullets[i] = new Bullet(0, -999);
	}
	while (!(Player::IsDead(player))) {	//game loop
		//KeepFrame(W_CONSOLE, H_CONSOLE);
		//LScroll(player, head);
		//RScroll(player, head);
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
		if (GetKeyState(VK_SPACE) < 0 && Player::FireCounter(player) == 0) {		//se sto premendo la barra spaziatrice sparo il primo proiettile disponibile
			Player::SetFireCounter(player);
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
		ShowDifficulty(head);
		if (!(Player::IsDead(player))) {		//aggiorna la posizione del giocatore e lo disegna
			Player::Erase(player);
			Player::Move(player);
			RScroll(player, head);
			LScroll(player, head);
			Player::Draw(player);
			if (Player::FireCounter(player) > 0) {
				Player::ReduceFireCounter(player);
			}
			if (Player::KCounter(player) > 0) {
				Player::ReduceKCounter(player);
			}
		}
		Sleep(75);
	}
	GameOver(player);
}
int main() {
	GameMenu();
}
void GameOver(Player player) {
	system("cls");
	set_console_size(99, 41);
	gioco::set_console_color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	/*cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";*/
	cout << "                  #######         ####        ####     #### #########\n"; Sleep(10);
	cout << "                 ##              ######       ## ##   ## ## ##\n"; Sleep(10);
	cout << "                ##              ###  ###      ##  ## ##  ## ##\n"; Sleep(10);
	cout << "               ##              ###    ###     ##   ###   ## ######\n"; Sleep(10);
	cout << "                ##   #####    ############    ##    #    ## ##\n"; Sleep(10);
	cout << "                 ##     ###  ###        ###   ##         ## ##\n"; Sleep(10);
	cout << "                  ########  ###          ###  ##         ## #########\n"; Sleep(10);
	cout << "\n"; Sleep(10);
	cout << "\n"; Sleep(10);
	cout << "\n"; Sleep(10);
	cout << "                   ######### ##           ## ######## ########    ###\n"; Sleep(10);
	cout << "                   ##     ##  ##         ##  ##       ##     ##   ###\n"; Sleep(10);
	cout << "                   ##     ##   ##       ##   ##       ##      ##  ###\n"; Sleep(10);
	cout << "                   ##     ##    ##     ##    ######   #########   ###\n"; Sleep(10);
	cout << "                   ##     ##     ##   ##     ##       ##  ##      ###\n"; Sleep(10);
	cout << "                   ##     ##      ## ##      ##       ##    ##       \n"; Sleep(10);
	cout << "                   #########       ###       ######## ##      ##  ###\n"; Sleep(10);
	Sleep(1000);
	cout << "Hai fatto " << player._points << " punti!\n";
	Sleep(500);
	if (player._points == 0) {
		cout << "Hai almeno letto il tutorial? :(\n";
	}
	else if (player._points < 1000) {
		cout << "Sei un po' scarso, ti consiglio di andare a rileggere il tutorial :)\n";
	}
	else if(player._points < 99999) { 
		cout << "Stai diventando bravo, per battermi dovrai fare piu' di 99999 punti \n"; 
	}
	else {
		cout << "COME HAI FATTO A BATTERMI!? "; Sleep(500); cout << " . "; Sleep(500); cout << " . "; Sleep(500); cout << " . "; Sleep(500); cout << " GG \n";
	}
	Sleep(5000);
	cout << "Vuoi riprovare ? Y/N ";
	while (1 != 0) {
		char risp = _getch();
		if (risp == 'n' || risp == 'N') {
			system("cls");
			GameMenu();
		}
		else if (risp == 'y' || risp == 'Y') {
			system("cls");
			GameLoop();
		}
	}
/*	cout << "░░░░░░░░░░░░╔═══╦═══╦═╗╔═╦═══╗░░░░░░░░░░";
	cout << "░░░░░░░░░░░░║╔═╗║╔═╗║║╚╝║║╔══╝░░░░░░░░░░";
	cout << "░░░░░░░░░░░░║║░╚╣║░║║╔╗╔╗║╚══╗░░░░░░░░░░";
	cout << "░░░░░░░░░░░░║║╔═╣╚═╝║║║║║║╔══╝░░░░░░░░░░";
	cout << "░░░░░░░░░░░░║╚╩═║╔═╗║║║║║║╚══╗░░░░░░░░░░";
	cout << "░░░░░░░░░░░░╚═══╩╝░╚╩╝╚╝╚╩═══╝░░░░░░░░░░";
	cout << "░░░░░░░░░░░░╔═══╦╗░░╔╦═══╦═══╗░░░░░░░░░░";
	cout << "░░░░░░░░░░░░║╔═╗║╚╗╔╝║╔══╣╔═╗║░░░░░░░░░░";
	cout << "░░░░░░░░░░░░║║░║╠╗║║╔╣╚══╣╚═╝║░░░░░░░░░░";
	cout << "░░░░░░░░░░░░║║░║║║╚╝║║╔══╣╔╗╔╝░░░░░░░░░░";
	cout << "░░░░░░░░░░░░║╚═╝║╚╗╔╝║╚══╣║║╚╗░░░░░░░░░░";
	cout << "░░░░░░░░░░░░╚═══╝░╚╝░╚═══╩╝╚═╝░░░░░░░░░░";
	*/
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