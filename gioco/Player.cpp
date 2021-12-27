#include "Player.h"
#include "gioco.h"
#include <Windows.h>
#include<iostream>

void Player::Move(Player& player) {
	if (GetKeyState(VK_LSHIFT) < 0) {
		player._shielded = true;
		gioco::set_console_color(FOREGROUND_INTENSITY);
		gioco::gotoxy(player._x + 1, player._y);
		putchar('|');
		gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	else {
		player._shielded = false;
		if ((gioco::scan_output(player._x + 1, player._y) == '|')) { gioco::gotoxy(player._x + 1, player._y); putchar(' '); }
		char sopra, sotto;
		sopra = gioco::scan_output(player._x, player._y - 1);
		sotto = gioco::scan_output(player._x, player._y + 1);
		if (GetKeyState(0x41) < 0 && player._x - 1 >= 0) { //sinistra
			player._x--;
		}
		if (GetKeyState(0x44) < 0 && player._x + 1 < W_CONSOLE) { //destra
			player._x++;
		}
		if (GetKeyState(0x57) < 0 && player._y - 2 >= 1 && sopra == 'I') {  //su
			player._y = player._y - 2;
		}
		if (GetKeyState(0x53) < 0 && player._y + 2 < H_CONSOLE && sotto == 'I') { //giu'
			player._y = player._y + 2;
		}
		while (gioco::scan_output(player._x, player._y + 1) == ' ') {
			player._y++;
		}
	}
}

void Player::Draw(Player player) {
	gioco::gotoxy(player._x, player._y);
	putchar(CHAR_NAVICELLA);
}
void Player::Erase(Player player) {
	gioco::gotoxy(player._x, player._y);
	putchar(' ');
}
/*
	if (GetKeyState(VK_LEFT) < 0 && gravsx) {

		x = x - 1 >= 0 ? x - 1 : x;							//sinistra
		y = y + 2 < H_CONSOLE ? y + 2 : y;
		gioco::gotoxy(x + 1, y - 2); putchar(' ');
		gioco::show_char_at(x, y, CHAR_NAVICELLA);

	}
	else if (GetKeyState(VK_LEFT) < 0 && (!gravsx)) {

		x = x - 1 >= 0 ? x - 1 : x;
		gioco::show_char_at(x, y, CHAR_NAVICELLA);

	}
	else if (GetKeyState(VK_RIGHT) < 0 && gravdx) {

		x = x + 1 < W_CONSOLE ? x + 1 : x;                  //destra
		y = y + 2 < H_CONSOLE ? y + 2 : y;
		gioco::gotoxy(x - 1, y - 2); putchar(' ');
		gioco::show_char_at(x, y, CHAR_NAVICELLA);

	}
	else if (GetKeyState(VK_RIGHT) < 0 && (!gravdx)) {

		x = x + 1 < W_CONSOLE ? x + 1 : x;
		gioco::show_char_at(x, y, CHAR_NAVICELLA);

	}
	else if (GetKeyState(VK_UP) < 0 && jump) {

		y = y - 2 >= 1 ? y - 2 : y;
		gioco::show_char_at(x, y, CHAR_NAVICELLA);//su 

	}
	else if (GetKeyState(VK_DOWN) < 0) {

		y = y + 2 < H_CONSOLE ? y + 2 : y;
		gioco::show_char_at(x, y, CHAR_NAVICELLA);		//giù

	}
}
*/