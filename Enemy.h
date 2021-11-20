#pragma once
#include <iostream>
//#include <string>

using namespace std;

class Enemy
{
private:
	string _name;
	char _tile;
/*	invece che avere il costruttore a cui passare nome e carattere del nemico,
*	possiamo fare una sottoclasse per ogni tipo di nemico
* 
*	NOTA: non so se il nome lo possiamo dare con la classe string...
*/

	//stats
	int _level;
	int _attack;
	int _defense;
	int _health;
	int _expValue;
	//Position
	int _x;
	int _y;

public:

	Enemy(string name, char tile, int level, int attack, int defense, int health, int xp);

	int attack();

	//setters
	void setPosition(int x, int y);

	//getters
	void getPosition(int& x, int& y);
	string getName() { return _name; }
	char getTile() { return _tile; }
	

	int takeDamage(int attack);

	//per far muovere i nemici, poi vediamo se farlo lol
	//char getMove(int playerX, int playerY);

};