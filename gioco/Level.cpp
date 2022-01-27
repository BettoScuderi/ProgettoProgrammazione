#include "Level.h"

void Level::LScrollLevel(Level& level) {	//scorri tutti gli oggetti nel livello di uno a sinistra
	level._xinizio--;
	level._xfine--;
	for (int i = 0; i < 10; i++) {
		if (Platform::ToDraw(*(level.platforms[i]))) {
			Platform::LScrollPlatform(*(level.platforms[i]));
			Enemy::LScrollEnemy(*(level.platforms[i]->_enemy));
			Powerup::LScrollPowerup(*(level.platforms[i]->_powerup));
		}
	}
}
void Level::RScrollLevel(Level& level) {		//scorri tutti gli oggetti nel livello di uno a destra
	level._xinizio++;
	level._xfine++;
	for (int i = 0; i < 10; i++) {
		if (Platform::ToDraw(*(level.platforms[i]))) {
			Platform::RScrollPlatform(*(level.platforms[i]));
			Enemy::RScrollEnemy(*(level.platforms[i]->_enemy));
			Powerup::RScrollPowerup(*(level.platforms[i]->_powerup));
		}
	}
}