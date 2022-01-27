#pragma once
#include <Windows.h>
#include "Player.h"

#define W_CONSOLE 80	
#define H_CONSOLE 20    
/* 
NEMICI
		L '\x1e'
L '\x111' 0 L'\x110' 
-0
|0

POWER UP
* Stella di Super Mario
@ Ricarica proiettili/aumento cadenza proiettili
$ scudo
L'\3' punti
8 killa tutti nemici visibili
*/

/*
**************************TO DO**********************************
-mettere qualcosa per terra cosi' non basta andare dritti per vincere (o anche no dato che andando dritti e basta non si fanno punti e lagga e basta quindi chi lo fa se lo merita tutto)
-in collisioni i nemici non sono da prendere in input direttamente ma basta la piattaforma e poi si usa platform._enemy(per pulizia di codice)
-fare un menu' iniziale con anche magari un tutorial contenente i vari nemici e powerup
*/

class gioco
{
public:
	static void show_char_at(int x, int y, wchar_t c);
	static void gotoxy(int x, int y);
	static void set_console_color(WORD color);
	static char scan_output(SHORT x, SHORT y);
	static void ShowPoints(Player player);
};

