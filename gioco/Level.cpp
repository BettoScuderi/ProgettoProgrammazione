#include "Level.h"

void Level::LScrollLevel(Level& level) {	//scorri tutti gli oggetti nel livello di uno a sinistra
	level._xinizio--;
	level._xfine--;
	for (int i = 0; i < 10; i++) {
		Enemy::LScrollEnemy(*(level.enemies[i]));
		Platform::LScrollPlatform(*(level.platforms[i]));
	}
}
void Level::RScrollLevel(Level& level) {		//scorri tutti gli oggetti nel livello di uno a destra
	level._xinizio++;
	level._xfine++;
	for (int i = 0; i < 10; i++) {
		Enemy::RScrollEnemy(*(level.enemies[i]));
		Platform::RScrollPlatform(*(level.platforms[i]));
	}
}