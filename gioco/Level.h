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
	Level(int difficulty, int xinizio, int xfine) {
		_difficulty = difficulty;
		_xinizio = xinizio;
		_xfine = xfine;
		for (int i = 0; i < 10; i++) {		//creo tutti gli oggetti all'interno del livello
			int pari = rand() % (H_CONSOLE - 8) + 2;
			while (pari % 2) {
				pari = rand() % (H_CONSOLE - 8) + 2;
			}
			platforms[i] = new Platform(rand() % 3 + xinizio, rand() % 5 + (xinizio + 5), pari);		//fa in modo che ogni piattaforma abbia almeno una casella di distanza in verticale tra una e l'altra
		}
		for (int i = 9 - difficulty; i > 0; i--) {		//in base alla difficolta' elimino un numero di nemici e piattaforme create
			Enemy::Die(*platforms[i]->_enemy);
			platforms[i]->_todraw = false;
		}
	}
	static int Xinizio(Level level) { return level._xinizio; };
	static int Xfine(Level level) { return level._xfine; };
	static int Difficulty(Level level) { return level._difficulty; };
	static void RScrollLevel(Level& level);
	static void LScrollLevel(Level& level);
};

