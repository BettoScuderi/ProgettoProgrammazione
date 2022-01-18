#include"gioco.h"
#include "Bullet.h"
#include "Player.h"
#include <Windows.h>
#include <iostream>


void Bullet::Draw(Bullet &bullet) {		//disegna il proiettile del giocatore spostandolo di uno in avanti
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	if (bullet._x < 80) {	//se e' nello schermo lo sposta
		bullet._x = bullet._x + 1;
		gioco::gotoxy(bullet._x, bullet._y); putchar('-');
		gioco::gotoxy(bullet._x - 1, bullet._y); putchar(' ');
	}
	else {		//altrimenti lo elimina
		Bullet::Die(bullet);
	}
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
void Bullet::FireBullet(Bullet& bullet, Player player) {		//spara il proiettile del giocatore
	bullet._isshot = true;
	bullet._x = Player::X(player)+1;
	bullet._y = Player::Y(player);
}
void Bullet::Die(Bullet& bullet) {		//elimina il proiettile
	gioco::gotoxy(bullet._x, bullet._y);
	putchar(' ');
	bullet._isebullet = false;
	bullet._isshot = false;
	bullet._x = 0;
	bullet._y = 0;
}
void Bullet::Collision(Enemy &enemy, Bullet& bullet, Player &player) {		//controlla eventuali collisioni fra il proiettile e un nemico o un giocatore
	if (Enemy::X(enemy) == Bullet::X(bullet) && Enemy::Y(enemy) == Bullet::Y(bullet) && !(Bullet::IsEBullet(bullet))) {		//se il proiettile del giocatore colpisce un nemico viene eliminato
		Enemy::Die(enemy);
		Bullet::Die(bullet);
		/* ricompensa per aver ucciso il nemico tipo : Player::Reward(player, 10)*/
	}
	if (Player::X(player) == Bullet::X(bullet) && Player::Y(player) == Bullet::Y(bullet)&& Bullet::IsEBullet(bullet)) {		//se il proiettile di un nemico colpisce il giocatore mentre non ha lo scudo viene eliminato e il giocatore perde vita/punti
		Bullet::Die(bullet);
		if (!(Player::Shielded(player))) {
			gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			exit(0);
		}
	}
}
void Bullet::FireEBullet(Bullet& bullet, Enemy enemy) {		//spara il proiettile del nemico
	bullet._isshot = true;
	bullet._isebullet = true;
	bullet._x = Enemy::X(enemy)-1;
	bullet._y = Enemy::Y(enemy);
}
void Bullet::EDraw(Bullet& bullet) {		//disegna il proiettile del nemico uno indietro		
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_GREEN);
	if (bullet._x > 0) {		//se e' nello schermo lo sposta
		bullet._x = bullet._x - 1;
		gioco::gotoxy(bullet._x, bullet._y); putchar('-');
		gioco::gotoxy(bullet._x + 1, bullet._y); putchar(' ');
	}
	else {		//altrimenti lo elimina
		Bullet::Die(bullet);
	}
	gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}