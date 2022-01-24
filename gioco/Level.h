#include "Platform.h"
#include "Enemy.h"
#include <ctime>
#pragma once
class Level
{
private:
	int _xinizio;
	int _xfine;
	int _difficulty;
public:
	Platform* platforms[10];
	Enemy *enemies[10];
	Level(int difficulty, int xinizio, int xfine) {
		_difficulty = difficulty;
		_xinizio = xinizio;
		_xfine = xfine;
		for (int i = 0; i < 10; i++) {		//creo tutti gli oggetti all'interno del livello
			int pari = rand() % (H_CONSOLE - 4) + 2;
			while (pari % 2) {
				pari = rand() % (H_CONSOLE - 4) + 2;
			}
			platforms[i] = new Platform(rand() % 5 + xinizio, rand() % 5 + (xinizio + 5), pari);
			enemies[i] = new Enemy(rand() % 10 + xinizio, rand() % (H_CONSOLE/2) +1, (100 - difficulty * 10));
		}
		for (int i = 9-difficulty; i > 0; i--) {		//in base alla difficolta' elimino un numero di nemici e piattaforme create
			Enemy::Die(*enemies[i]);
		}
		for (int i = 0; (i <= difficulty && i < 10); i++) {
			platforms[i]->_todraw = true;
		}
	}
	static int Xinizio(Level level) { return level._xinizio; };
	static int Xfine(Level level) { return level._xfine; };
	static int Difficulty(Level level) { return level._difficulty; };
	static void RScrollLevel(Level& level);
	static void LScrollLevel(Level& level);
};


/* POWER UP
* Stella di Super Mario
@ Ricarica proiettili/aumento cadenza proiettili
$ scudo
L'\3' punti
8 killa tutti nemici visibili
*/

