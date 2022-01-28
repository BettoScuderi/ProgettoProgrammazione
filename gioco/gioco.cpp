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

struct lvlbilist {			//bilista di blocchi di mappa
	lvlbilist* prev  =NULL;
	Level lvl= Level::Level(0,0,0);
	lvlbilist* next = NULL;
};
typedef lvlbilist* lvlptr;
void GameMenu();		//dichiarazione funzioni definite in seguito
void Tutorial();
void GameLoop();
void GameOver(Player player);
char gioco::scan_output(SHORT x, SHORT y) {		//restituisce il carattere presente alle coordinate in input
	LPWSTR buffer = new wchar_t[1];
	DWORD dwChars;
	ReadConsoleOutputCharacterW(gHndConsole, buffer, 1, { x,y }, &dwChars);
	char mio = *buffer;	
	return mio;
}
void show_console_cursor(bool show) {	//mostra o nasconde il cursore in base al booleano in input
	CONSOLE_CURSOR_INFO ci;
	GetConsoleCursorInfo(gHndConsole, &ci);
	ci.bVisible = show ? TRUE : FALSE;
	SetConsoleCursorInfo(gHndConsole, &ci);
}

void set_console_size(int wConsole, int hConsole) {		//prende in input e quindi imposta la dimensione del buffer dello schermo e della finestra della console
	COORD dim = { wConsole, hConsole };
	SMALL_RECT sr = { 0, 0, wConsole, hConsole};
	SetConsoleScreenBufferSize(gHndConsole, dim);
	SetConsoleWindowInfo(gHndConsole, TRUE, &sr);
}

void gioco::set_console_color(WORD color) {		//imposta il colore del carattere della console
	SetConsoleTextAttribute(gHndConsole, color);
}

void gioco::gotoxy(int x, int y) {		//posiziona il cursore alle coordinate in input
	if (x >= 0 && x <= W_CONSOLE && y >= 0 && y <= H_CONSOLE) {
		COORD coord = { x, y };
		SetConsoleCursorPosition(gHndConsole, coord);
	}
}
void init_console(int wConsole, int hConsole, Player& player) {		//inizializza la console
	for (int i = 0; i <= wConsole; i++) {		//disegna il terreno e il cielo della mappa
		gioco::set_console_color(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		gioco::gotoxy(i, 0); putchar(219);
		gioco::set_console_color(FOREGROUND_GREEN | BACKGROUND_GREEN);
		gioco::gotoxy(i, (hConsole-4)); putchar(219);
	}
	gioco::set_console_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);		//disegna l'interfaccia grafica
	gioco::gotoxy(W_CONSOLE - 12, H_CONSOLE - 2);
	cout << "DIFFICOLTA':";
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
	for (int i = 0; i < Player::Lives(player); i++) {
		gioco::gotoxy(i, H_CONSOLE - 3);
		putchar(3);
	}
	gioco::set_console_color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	gioco::gotoxy(0, H_CONSOLE - 1);
	cout << "PUNTEGGIO:0";
	gioco::ShowPoints(player);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	show_console_cursor(false);
}
void Tutorial() {		//stampa la schermata di tutorial
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
	while (1 != 0) {		//il ciclo continua fino a quando il giocatore non preme q per tornare al menu'
		char back = _getch();
		if (back == 'q' || back == 'Q') {
			system("cls");
			GameMenu();
		}
	}
}

void GameMenu() {	//stampa il menu' iniziale
	show_console_cursor(false);
	SetConsoleTitleW(L"Bully");
	set_console_size(W_CONSOLE, H_CONSOLE);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	gioco::gotoxy((W_CONSOLE/2)-4, ((H_CONSOLE/2)-2));
	cout << "1-PLAY\n";
	gioco::gotoxy((W_CONSOLE / 2) - 6, (H_CONSOLE / 2));
	cout << "2-TUTORIAL\n";
	gioco::gotoxy((W_CONSOLE / 2) - 4, ((H_CONSOLE / 2) + 2));
	cout << "3-EXIT\n";
	while (1 != 0) {		//il ciclo continua fino a quando il giocatore non selezione una voce del menu' 
		char sel;
		sel = _getch();
		if (sel == '1') {
			system("cls");
			GameLoop();		//se schiaccia '1' inizia il gioco chiamando GameLoop
		}
		else if (sel == '2') {
			Tutorial();		//se schiaccia '2' viene portato alla schermata di tutorial
		}
		else if (sel == '3') {		//se schiaccia '3' viene mostrato un messaggio di saluti e viene chiuso il gioco
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

int bilist_length(lvlptr head) {		//restituisce la lunghezza della bilista partendo dal puntatore in input (generalmente punta il primo elemento della stessa)
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
	int diff = bilist_length(head)/8;
	if (diff > 9) {
		diff = 9;
	}
	q = new lvlbilist;
	tail->next = q;
	(q)->lvl = Level::Level(diff, Level::Xfine(tail->lvl)+1, Level::Xfine(tail->lvl) + 10);	//nuovo livello da generare
	(q)->prev = tail;
	tail = q;
}
void Genero(lvlptr &tail, lvlptr head) {		//fino a quando l'ultimo blocco della bilista non esce dallo schermo ne genera uno nuovo da mettere in fondo
	while (Level::Xfine(tail->lvl)<W_CONSOLE) {
		Tail_ins(tail, head);
	}
}
void KeepFscreenlvl(lvlptr &fscreenlvl) {		//mantiene fscreenlvl a puntare il primo blocco di mappa dello schermo
	if (Level::Xfine(fscreenlvl->lvl) < 0) {
		fscreenlvl = fscreenlvl->next;
	}
	else if (Level::Xfine(fscreenlvl->lvl) > 9) {
		fscreenlvl = fscreenlvl->prev;
	}
}
void KeepLscreenlvl(lvlptr &lscreenlvl) {		//mantiene lscreenlvl a puntare l'ultimo blocco di mappa dello schermo
	if (Level::Xfine(lscreenlvl->lvl) < W_CONSOLE) {
		lscreenlvl = lscreenlvl->next;
	}
	else if (Level::Xinizio(lscreenlvl->lvl) > W_CONSOLE) {
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
void ShowDifficulty(lvlptr head) {		//aggiorna il campo della difficolta' nell'interfaccia
	int diff = (bilist_length(head)/8);
	if (diff > 9) {
		diff = 9;
	}
	gioco::set_console_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	gioco::gotoxy(W_CONSOLE, (H_CONSOLE - 2));
	putchar(diff+48);
}
void gioco::ShowPoints(Player player) {		//aggiorna il campo dei punti nell'interfaccia
	gioco::set_console_color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	for (int i = 10; i <= W_CONSOLE; i++) {		//cancella tutti i caratteri sulla riga di "PUNTEGGIO:" per far spazio al nuovo punteggio
		gioco::gotoxy(i, H_CONSOLE - 1);
		putchar(' ');
	}
	gioco::gotoxy(10, H_CONSOLE - 1);
	cout << player._points;
}
void UpdateScreenLvl(lvlptr fscreenlvl, lvlptr lscreenlvl, Bullet *bullets[], Player& player) {		//aggiorna tutti gli oggetti nello schermo
	lvlptr ptr = fscreenlvl;
	while (ptr != lscreenlvl->next) {		//scorre dal primo blocco di mappa visibile fino all'ultimo blocco visibile
		if (Player::Nuke(player)) {		//controlla se il giocatore ha preso il power-up nuke e comincia a eliminare ogni nemico vivo all'interno di ogni blocco visibile
			lvlptr lptr = fscreenlvl;
			while (lptr != lscreenlvl->next) {
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
			if (Platform::ToDraw(*ptr->lvl.platforms[i])) {				//scorre ogni piattaforma ridisegnando ogni piattaforma, nemico e power-up
				Platform::Erase(*ptr->lvl.platforms[i]);
				Platform::Draw(*ptr->lvl.platforms[i]);
				Powerup::Erase(*ptr->lvl.platforms[i]->_powerup);
				Powerup::Draw(*ptr->lvl.platforms[i]->_powerup);
				Powerup::Collision(*ptr->lvl.platforms[i]->_powerup, player);	//controlla la collisione fra il player e il power-up
				Enemy::Collision(*ptr->lvl.platforms[i]->_enemy, player);		//controlla la collisione fra il player e il nemico
				if (Enemy::FireCounter(*ptr->lvl.platforms[i]->_enemy) == Enemy::FireRate(*ptr->lvl.platforms[i]->_enemy)) {	//il contatore per sparare ha raggiunto il valore per poter sparare
					Enemy::ZeroCounter(*ptr->lvl.platforms[i]->_enemy);		//azzera il contatore
					for (int j = 0; j < 100; j++) {			//spara il primo proiettile disponibile
						if (!(Bullet::IsShot(*bullets[j]))) {
							Bullet::FireEBullet(*bullets[j], *ptr->lvl.platforms[i]->_enemy);
							j = 100;
						}

					}
				}
				else { Enemy::Sparerai(*ptr->lvl.platforms[i]->_enemy); }	//altrimenti aumenta di 1 il contatore per sparare
				if (!(Enemy::IsDead(*ptr->lvl.platforms[i]->_enemy))) {	//ogni nemico viene disegnato
					Enemy::Draw(*ptr->lvl.platforms[i]->_enemy);
				}
			}
		}
		for (int i = 0; i < 10; i++) {		//per ogni piattaforma
			for (int j = 0; j < 100; j++) {		//e per ogni proiettile sparato
				if (Bullet::IsShot(*bullets[j])) {
					Bullet::Collision(*ptr->lvl.platforms[i]->_enemy, *bullets[j], player, *ptr->lvl.platforms[i]);		//controlla se un proiettile occupa la stessa posizione di un nemico o del giocatore o se si ferma contro una piattaforma
				}
			}
		}
		ptr = ptr->next;		//sposta il puntatore per scorrere tutti i blocchi di mappa visibili
	}
}
void GameLoop() {	//contiene l'inizializzazione e il ciclo di gioco
	srand(time(NULL));
	lvlptr head, tail;	//inizializza i primi due puntatori a blocchi di mappa
	head = new lvlbilist;
	head->prev = NULL;
	head->lvl = Level::Level(0, 0, 9); //questo sara' sempre il primo blocco di mappa e head punta sempre ad esso
	tail = new lvlbilist;
	tail->prev = head;
	tail->next = NULL;
	tail->lvl = Level::Level(0, 10, 19);
	head->next = tail;
	lvlptr first_screen_lvl, last_screen_lvl;	//inizializza i due puntatori che punteranno sempre il primo e l'ultimo blocco di mappa visibile
	first_screen_lvl = head;
	last_screen_lvl = tail;
	int x = 0;			//coordinate iniziali del giocatore
	int y = H_CONSOLE - 5;
	Bullet *bullets[100];		//dichiara il puntatore ad array di proiettili
	Player player = Player(x, y);		//genera il giocatore
	init_console(W_CONSOLE, H_CONSOLE, player);	//inizializza la console
	for (int i = 0; i < 100; i++) {		//inizializza tutti i proiettili
		bullets[i] = new Bullet(0, -999);
	}
	while (!(Player::IsDead(player))) {	//game loop che continua fino alla morte del giocatore (Game Over)
		if (GetKeyState(VK_ESCAPE) < 0) {		//se il giocatore preme 'ESC' torna al menu' chiudendo la partita attuale
			system("cls");
			GameMenu();
		}
		Genero(tail, head);			//controllo se devo generare un blocco di mappa in coda e in base a quanti ce ne sono nella bilista cambiera' la sua difficolta'
		KeepFscreenlvl(first_screen_lvl);		//mantengo first_screen_lvl e last_screen_lvl al primo e ultimo blocco visibile
		KeepLscreenlvl(last_screen_lvl);
		UpdateScreenLvl(first_screen_lvl, last_screen_lvl, bullets, player);		//aggiorno tutte le entita' visibili all'interno dei blocchi di mappa (piattaforme, nemici e power-up) controllando le collisioni
		if (GetKeyState(VK_SPACE) < 0 && Player::FireCounter(player) == 0) {		//se sto premendo la barra spaziatrice ed e' passato abbastanza tempo dall'ultima volta che ho sparato sparo il primo proiettile disponibile
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
		show_console_cursor(false);			//evita che il cursore torni visibile
		ShowDifficulty(head);			//aggiorna la difficolta' nell'interfaccia
		if (!(Player::IsDead(player))) {		//aggiorna la posizione del giocatore e lo disegna
			Player::Erase(player);
			Player::Move(player);
			RScroll(player, head);		//fa scorrere i blocchi di livello se il giocatore si trova nella parte sinistra o destra dello schermo dopo il movimento
			LScroll(player, head);
			Player::Draw(player);
			if (Player::FireCounter(player) > 0) {		//aggiorna il contatore del giocatore che gestisce dla cadenza di fuoco
				Player::ReduceFireCounter(player);
			}
			if (Player::KCounter(player) > 0) {		//aggiorna il contatore del giocatore che gestisce l'invincibilita'
				Player::ReduceKCounter(player);
			}
		}
		Sleep(75);		//ogni quanto si aaggiorna lo schermo
	}
	GameOver(player);		//funzione di GameOver
}
int main() {		//lancia il GameMenu da cui poi si possono lanciare le varie Tutorial, GameLoop e GameOver
	GameMenu();
}
void GameOver(Player player) {		//stampa la schermata di GameOver con messaggi diversi in base ai punti effettuati nella partita
	system("cls");
	gioco::set_console_color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
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
	cout << "Vuoi riprovare ? Y/N ";		//consente al giocatore di ricominciare immediatamente una nuova partita o di tornare al menu' principale
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

}