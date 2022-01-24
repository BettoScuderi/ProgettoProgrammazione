#include "Enemy.h"
#include "gioco.h"
#include <Windows.h>
#include <iostream>

void Enemy::Draw(Enemy &enemy) {		//disegna il nemico se si trova nello schermo
	if (!(IsDead(enemy))&&enemy._x>-1&&enemy._x<79) {
		gioco::gotoxy(enemy._x, enemy._y);
		putchar(' ');
		gioco::set_console_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
		gioco::gotoxy(enemy._x, enemy._y);
		putchar(CHAR_NAVICELLA);
		gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
}
void Enemy::Move(Enemy &enemy) {		//applica la gravita' al nemico se si trova nello schermo
	if (enemy._x > 0 && enemy._x < 79) {
		while (gioco::scan_output(enemy._x, enemy._y + 1) == ' ') {
			gioco::gotoxy(enemy._x, enemy._y);
			putchar(' ');
			enemy._y++;
		}
	}
}
void Enemy::Erase(Enemy& enemy) {		//elimina il carattere del nemico se si trova nello schermo
	if (enemy._x > -1 && enemy._x < 80) {
		gioco::gotoxy(enemy._x, enemy._y);
		putchar(' ');
	}
}
void Enemy::Die(Enemy &enemy) {		//elimina il nemico
	gioco::gotoxy(enemy._x, enemy._y);
	putchar(' ');
	enemy._isdead = true;
	enemy._x = 0;
	enemy._y = 0;
}
void Enemy::Sparerai(Enemy &enemy) {		//aumenta di 1 il contatore per sparare del nemico se si trova nello schermo
	if(enemy._x>-1 && enemy._x <80)
	enemy._firecounter++;
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