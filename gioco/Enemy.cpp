#include "Enemy.h"
#include "gioco.h"
#include <Windows.h>
#include<iostream>

void Enemy::Draw(Enemy &enemy) {
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
	gioco::gotoxy(enemy._x, enemy._y);
	putchar(CHAR_NAVICELLA);
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void Enemy::Move(Enemy &enemy) {
	while (gioco::scan_output(enemy._x, enemy._y+1 ) == ' ') {
		enemy._y++;
	}
}
void Enemy::Die(Enemy &enemy) {
	gioco::gotoxy(enemy._x, enemy._y);
	putchar(' ');
	enemy._isdead = true;
	enemy._x = 0;
	enemy._y = 0;
}
void Enemy::Sparerai(Enemy & enemy) {
	enemy._firecounter++;
}