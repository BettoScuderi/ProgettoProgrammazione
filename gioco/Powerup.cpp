#include "Powerup.h"
#include "gioco.h"
#include <iostream>

void Powerup::Collision(Powerup& powerup, Player& player) {	//se il giocatore in input occupa le stessa casella del power-up allora ottiene il bonus e il power-up viene eliminato
	if (Powerup::X(powerup) == Player::X(player) && (Powerup::Y(powerup) == Player::Y(player)|| Powerup::Y(powerup) == (Player::Y(player)+1)) && !(Powerup::IsDead(powerup))) {
		Powerup::Bonus(powerup, player);
		Powerup::Die(powerup);
	}
}
void Powerup::Die(Powerup& powerup) {		//elimina il power-up
	Powerup::Erase(powerup);
	powerup._isdead = true;
	powerup._x = -999;
	powerup._y = 0;
}
void Powerup::Draw(Powerup powerup) {		//disegna il power-up
	if (powerup._x > -1 && powerup._x <= W_CONSOLE && !(powerup._isdead)) {
		gioco::gotoxy(powerup._x, powerup._y);
		putchar(' ');
		gioco::set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		gioco::gotoxy(powerup._x, powerup._y);
		putchar(powerup._char);
		gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
}
void Powerup::Erase(Powerup powerup) {		//cancella il carattere del power-up
	if (powerup._x > -1 && powerup._x <= W_CONSOLE) {
		gioco::gotoxy(powerup._x, powerup._y);
		putchar(' ');
	}
}
void Powerup::Bonus(Powerup& powerup, Player& player) {		//in base al tipo di power-up chiama la funzione Bonus associata, aggiorna anche l'interfaccia dei punti
	player._points = player._points + 10;
	gioco::ShowPoints(player);
	if (powerup._bonus == 1) {
		Shield::Bonus(player);
	}
	else if (powerup._bonus == 2) {
		Ratio::Bonus(player);
	}
	else if (powerup._bonus == 3) {
		Star::Bonus(player);
	}
	else if (powerup._bonus == 4) {
		Heart::Bonus(player);
	}
	else if (powerup._bonus == 5) {
		Nuke::Bonus(player);
	}
}
void Powerup::RScrollPowerup(Powerup& powerup) {		//fa scorrere il power-up di uno a destra/sinistra
	Powerup::Erase(powerup);
	powerup._x++;
	Powerup::Draw(powerup);
}
void Powerup::LScrollPowerup(Powerup& powerup) {
	Powerup::Erase(powerup);
	powerup._x--;
	Powerup::Draw(powerup);
}

void Ratio::Bonus(Player& player) {		//aumenta la cadenza di fuoco
	if (Player::FireRatio(player) > 4) {
		player._fireratio = player._fireratio - 3;
	}
}

void Star::Bonus(Player& player) {		//rende invincibili per 150 cicli del GameLoop
	Player::SetKCounter(player, 150);
}

void Heart::Bonus(Player& player) {		//aumenta di uno le vite del giocatore
	Player::OneUp(player);
}
