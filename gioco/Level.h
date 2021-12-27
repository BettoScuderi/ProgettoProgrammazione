#pragma once
class Level
{
private:
	int _difficulty;
public:
	Level(int difficulty) {
		_difficulty = difficulty;
	}
	static int Difficulty(Level level) { return level._difficulty; }
	static void GeneratePlatforms(Level level);
};

