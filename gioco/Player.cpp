#include "Player.h"
#include "gioco.h"
#include <Windows.h>
#include<iostream>

void Player::Move(Player& player) {		//muove il giocatore
	if (GetKeyState(VK_LSHIFT) < 0 && player._shielded) {		//se shift e' premuto attiva lo scudo del giocatore (se disponibile)
		gioco::set_console_color(FOREGROUND_INTENSITY);
		gioco::gotoxy(player._x + 1, player._y);
		putchar('|');
		gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	else {		//se il giocatore non sta attivando lo scudo in base all'input lo sposta a...
		if ((gioco::scan_output(player._x + 1, player._y) == '|')) { gioco::gotoxy(player._x + 1, player._y); putchar(' '); }
		if (GetKeyState(0x4F) < 0 && GetKeyState(0x50) < 0) {		//cheat "O+P" per impostare i punti a 99999 e quindi attivare la frase simpatica nella schermata di game over
			player._points = 99999;
		}
		if (GetKeyState(0x41) < 0 && player._x - 1 >= 0) { //sinistra
			player._x--;
		}
		if (GetKeyState(0x44) < 0 ) { //destra
			player._x++;
		}
		if (GetKeyState(0x57) < 0) {  //su
			if (player._y == H_CONSOLE - 1 ) {
				while (player._y == (H_CONSOLE-5)|| gioco::scan_output(player._x, player._y + 1) == ' ' && player._y>1) {		//se sono a terra o finche' non ho raggiunto una piattaforma vado in su di 1
					player._y--;
				}
			}
			else {
				while ( gioco::scan_output(player._x, player._y - 1) == ' ' && player._y > 1) {		//se sono gia' su una piattaforma finche' non ho una piattaforma sopra salgo...
					player._y--;
			}
				if (player._y > 2) {		//raggiunta la piattaforma ci vado sopra
					player._y = player._y - 2;
				}
			}
		}
		if (GetKeyState(0x53) < 0 && player._y + 2 < H_CONSOLE-4 ) { //giu'
			player._y = player._y + 2;
		}
		while (gioco::scan_output(player._x, player._y + 1) == ' ') {		//applica la gravita' al giocatore
			player._y++;
		}
	}
}

void Player::Draw(Player player) {		//disegna il giocatore
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	gioco::gotoxy(player._x, player._y);
	putchar(Player::CharPl(player));
}
void Player::Erase(Player player) {		//cancella il carattere del giocatore
	gioco::gotoxy(player._x, player._y);
	putchar(' ');
}
void Player::OneUp(Player& player) {		//aumenta le vite di uno e aggiorna i cuori nell'interfaccia
	player._lives++;
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
	for (int i = 0; i < player._lives; i++) {
		gioco::gotoxy(i, H_CONSOLE - 3);
		putchar(3);
	}
}
void Player::OneDown(Player& player) {		//diminuisce le vite di uno e se arrivano e zero il giocator muore
	player._lives--; 
	SetKCounter(player, 20);
	gioco::gotoxy(player._lives, H_CONSOLE - 3);
	putchar(' ');
	if (player._lives == 0) { 
		player._isdead = true;
	}
}
void Player::LScrollPlayer(Player& player) {		//sposta il giocatore di uno a sinistra
	Player::Erase(player);
	player._x--;
	Player::Draw(player);
}
void Player::RScrollPlayer(Player& player) {		//sposta il giocatore di uno a destra
	Erase(player);
	player._x++;
	Draw(player);
}