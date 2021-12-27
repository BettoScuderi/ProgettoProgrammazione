#include"gioco.h"
#include "Bullet.h"
#include "Player.h"
#include <Windows.h>
#include <iostream>


void Bullet::Draw(Bullet &bullet) {
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	if (bullet._x < 82) {
		bullet._x = bullet._x + 1;
		gioco::gotoxy(bullet._x, bullet._y); putchar('-');
		gioco::gotoxy(bullet._x - 1, bullet._y); putchar(' ');
	}
	else {
		Bullet::Die(bullet);
	}
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void Bullet::FireBullet(Bullet& bullet, Player player) {
	bullet._isshot = true;
	bullet._x = Player::X(player)+1;
	bullet._y = Player::Y(player);
}
void Bullet::Die(Bullet& bullet) {
	gioco::gotoxy(bullet._x, bullet._y);
	putchar(' ');
	bullet._isebullet = false;
	bullet._isshot = false;
	bullet._x = 0;
	bullet._y = 0;
}
void Bullet::Collision(Enemy& enemy, Bullet& bullet, Player &player) {
	if (Enemy::X(enemy) == Bullet::X(bullet) && Enemy::Y(enemy) == Bullet::Y(bullet)) {
		Enemy::Die(enemy);
		Bullet::Die(bullet);
		/* ricompensa per aver ucciso il nemico tipo : Player::Reward(player, 10)*/
	}
	if (Player::X(player) == Bullet::X(bullet) && Player::Y(player) == Bullet::Y(bullet)) {
		Bullet::Die(bullet);
		if (!(Player::Shielded(player))) {
			gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			exit(0);
		}
	}
}
void Bullet::FireEBullet(Bullet& bullet, Enemy enemy) {
	bullet._isshot = true;
	bullet._isebullet = true;
	bullet._x = Enemy::X(enemy)-1;
	bullet._y = Enemy::Y(enemy);
}
void Bullet::EDraw(Bullet& bullet) {
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_GREEN);
	if (bullet._x > 0) {
		bullet._x = bullet._x - 1;
		gioco::gotoxy(bullet._x, bullet._y); putchar('-');
		gioco::gotoxy(bullet._x + 1, bullet._y); putchar(' ');
	}
	else {
		Bullet::Die(bullet);
	}
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}