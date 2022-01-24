#include "Powerup.h"
#include "gioco.h"
#include <iostream>

bool Collision(Powerup& powerup, Player& player) {
	if (Powerup::X(powerup) == Player::X(player) && Powerup::Y(powerup) == Player::Y(player) && !(Powerup::IsDead(powerup))) {
		Powerup::Die(powerup);
		return true;
	}
	else return false;
}
void Powerup::Die(Powerup& powerup) {
	powerup._isdead = true;
	powerup._x = 0;
	powerup._y = 0;
}
void Powerup::Draw(Powerup powerup) {
	if (powerup._x > -1 && powerup._x < 80 && !(powerup._isdead)) {
		gioco::gotoxy(powerup._x, powerup._y);
		putchar(' ');
		gioco::set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		gioco::gotoxy(powerup._x, powerup._y);
	}
}



void Shield::Draw(Shield shield) {
	Powerup::Draw(shield);
	putchar(shield._charsh);
}