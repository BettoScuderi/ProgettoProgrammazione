#pragma once
#include <iostream>
//#include <string>

using namespace std;

class Enemy
{
private:
	//stats
	//int _attack;	LA PASSIAMO SINGOLARMENTE NELLE SOTTOCLASSI
	int _health;
	int _pointsValue;
	//Position
	int _x;
	int _y;

public:

	Enemy(/*int attack,*/ int health, int pointsValue);

	int attack();

	//setters
	void setPosition(int x, int y);

	//getters
	void getPosition(int& x, int& y);
	
	int takeDamage(int attack);

	//per far muovere i nemici, poi vediamo se farlo lol
	//char getMove(int playerX, int playerY);

};
