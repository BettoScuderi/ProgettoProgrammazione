#include "Enemy.h"
#include "gioco.h"
#include <Windows.h>
#include <iostream>

void Enemy::Draw(Enemy &enemy) {		//disegna il nemico se si trova nello schermo
	if (!(IsDead(enemy))&&enemy._x>-1&&enemy._x<=W_CONSOLE) {
		gioco::gotoxy(enemy._x, enemy._y);
		putchar(' ');
		gioco::set_console_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
		gioco::gotoxy(enemy._x, enemy._y);
		putchar(enemy._char);
		gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
}
void Enemy::Erase(Enemy& enemy) {		//elimina il carattere del nemico se si trova nello schermo
	if (enemy._x > -1 && enemy._x <= W_CONSOLE) {
		gioco::gotoxy(enemy._x, enemy._y);
		putchar(' ');
	}
}
void Enemy::Die(Enemy &enemy) {		//elimina il nemico
	gioco::gotoxy(enemy._x, enemy._y);
	putchar(' ');
	enemy._isdead = true;
	enemy._x = -999;
	enemy._y = 0;
}
void Enemy::Collision(Enemy& enemy, Player& player) {		//controlla se il nemico e il giocatore si trovano nella stessa casella e in base al tipo di nemico ferisce il giocatore o elimina il nemico aggiornando i punti
	if (Player::X(player) == Enemy::X(enemy) && (Player::Y(player) == Enemy::Y(enemy) || Player::Y(player)+1 == Enemy::Y(enemy))) {
		if (Enemy::Spiky(enemy) && Player::Killable(player)) {
			Player::OneDown(player);
		}
		else if (!(Enemy::Spiky(enemy))) {
			Enemy::Die(enemy);
			player._points = player._points + 30;
			gioco::ShowPoints(player);
		}
	}
}
void Enemy::LScrollEnemy(Enemy& enemy) {		//sposta il nemico di uno a sinistra
	Enemy::Erase(enemy);
	enemy._x--;
	Enemy::Draw(enemy);
}
void Enemy::RScrollEnemy(Enemy& enemy) {		//sposta il nemico di uno a destra
	Enemy::Erase(enemy);
	enemy._x++;
	Enemy::Draw(enemy);
}
void Enemy::Sparerai(Enemy& enemy) {		//aumenta di 1 il contatore per sparare del nemico se si trova nello schermo
	if (enemy._x > -1 && enemy._x <= W_CONSOLE)
		enemy._firecounter++;
}