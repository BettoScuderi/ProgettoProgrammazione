#pragma once

using namespace std;

class Player
{
private:
	//stats
	int _health;
	int _attack;
	int _points;
	//position
	int _x;
	int _y;

public:
	Player(int health, int attack);

	int attack();

	//setters
	void setPosition(int x, int y);

	//getters
	void getPosition(int& x, int& y);

	int takeDamage(int attack);

	void addPoints(int points);
};
