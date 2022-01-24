#pragma once
#include <Windows.h>

#define W_CONSOLE 80
#define H_CONSOLE 20
#define CHAR_NAVICELLA L'\xb0'
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
-Mettere i nemici che si generano sulle piattaforme
-Differenziare i nemici (con le spine, con lo scudo, che sparano)
-Mettere i powerup che si generano sulle piattaforme
-Differenziare i powerup (invincibilita', nuke, proiettili + veloci, punti/vita)
-fixare le scroll in modo da includere powerup e nemici sulle piattaforme
-fixare gli update in gioco.cpp perche' enemy adesso sono uno per piattaforma (prima erano liberi nel livello)\
-in collisioni i nemici non sono da prendere in input direttamente ma basta la piattaforma e poi si usa platform._enemy
-cambiare il sistema dei proiettili per renderlo meno laser beam, quindi sparo solo un proiettile ogni tot e non un flusso di proiettili, modificabile dal bonus
-volendo cambiare i caratteri delle cose se funziona tutto comunque
*/

class gioco
{
public:
	static void show_char_at(int x, int y, wchar_t c);
	static void gotoxy(int x, int y);
	static void set_console_color(WORD color);
	static char scan_output(SHORT x, SHORT y);
};

