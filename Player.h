#pragma once

using namespace std;

class Player
{
private:
	//stats
	int _level;
	int _health;
	int _attack;
	int _defense;
	int _exp;
	//position
	int _x;
	int _y;

public:
	Player();

	void init(int level, int health, int attack, int defense, int experience);
	//si puo' togliere questa funzione e fare direttamente con il costruttore?

	int attack();

	//setters
	void setPosition(int x, int y);

	//getters
	void getPosition(int& x, int& y);

	int takeDamage(int attack);

	void addExperience(int experience);
};