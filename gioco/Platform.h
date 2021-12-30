#pragma once
class Platform
{
private:
	int _length;
	int _height;
	bool _drawn;
public:
	Platform(int length, int height) {
		_length = length;
		_height = height;
		_drawn = false;
	}
	static void Draw(Platform platform);

};

