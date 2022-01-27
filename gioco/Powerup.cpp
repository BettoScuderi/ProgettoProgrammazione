#include "Powerup.h"
#include "gioco.h"
#include <iostream>

void Powerup::Collision(Powerup& powerup, Player& player) {
	if (Powerup::X(powerup) == Player::X(player) && (Powerup::Y(powerup) == Player::Y(player)|| Powerup::Y(powerup) == (Player::Y(player)+1)) && !(Powerup::IsDead(powerup))) {
		Powerup::Bonus(powerup, player);
		Powerup::Die(powerup);
	}
}
void Powerup::Die(Powerup& powerup) {
	Powerup::Erase(powerup);
	powerup._isdead = true;
	powerup._x = -999;
	powerup._y = 0;
}
void Powerup::Draw(Powerup powerup) {
	if (powerup._x > -1 && powerup._x <= W_CONSOLE && !(powerup._isdead)) {
		gioco::gotoxy(powerup._x, powerup._y);
		putchar(' ');
		gioco::set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		gioco::gotoxy(powerup._x, powerup._y);
		putchar(powerup._char);
		gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
}
void Powerup::Erase(Powerup powerup) {
	if (powerup._x > -1 && powerup._x <= W_CONSOLE) {
		gioco::gotoxy(powerup._x, powerup._y);
		putchar(' ');
	}
}
void Powerup::Bonus(Powerup& powerup, Player& player) {
	player._points = player._points + 10;
	gioco::ShowPoints(player);
	if (powerup._bonus == 1) {
		player._shielded = true;
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
void Powerup::RScrollPowerup(Powerup& powerup) {
	Powerup::Erase(powerup);
	powerup._x++;
	Powerup::Draw(powerup);
}
void Powerup::LScrollPowerup(Powerup& powerup) {
	Powerup::Erase(powerup);
	powerup._x--;
	Powerup::Draw(powerup);
}



void Shield::Draw(Shield shield) {
	Powerup::Draw(shield);
	putchar(shield._char);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void Shield::Collision(Shield& shield, Player& player) {
	Powerup::Collision(shield, player);
	Shield::Bonus(player);
}


void Ratio::Draw(Ratio ratio) {
	Powerup::Draw(ratio);
	putchar(ratio._char);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void Ratio::Collision(Ratio& ratio, Player& player) {
	Powerup::Collision(ratio, player);
	Ratio::Bonus(player);
}
void Ratio::Bonus(Player& player) {
	if (Player::FireRatio(player) > 4) {
		player._fireratio = player._fireratio - 3;
	}
}

void Star::Draw(Star star) {
	Powerup::Draw(star);
	putchar(star._char);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void Star::Collision(Star& star, Player& player) {
	Powerup::Collision(star, player);
	Star::Bonus(player);
}
void Star::Bonus(Player& player) {
	Player::SetKCounter(player, 150);
}

void Heart::Draw(Heart heart) {
	Powerup::Draw(heart);
	putchar(heart._char);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void Heart::Collision(Heart& heart, Player& player) {
	Powerup::Collision(heart, player);
	Heart::Bonus(player);
}
void Heart::Bonus(Player& player) {
	Player::OneUp(player);
}

void Nuke::Draw(Nuke nuke) {
	Powerup::Draw(nuke);
	putchar(nuke._char);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void Nuke::Collision(Nuke& nuke, Player& player) {
	Powerup::Collision(nuke, player);
	Nuke::Bonus(player);
}