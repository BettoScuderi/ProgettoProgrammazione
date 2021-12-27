#pragma once
class Platform
{
private:
	int _length;
	int _width;
	int _height;
	bool _drawn;
public:
	Platform(int length, int width, int height) {
		_length = length;
		_width = width;
		_height = height;
		_drawn = false;
	}
	static void Draw(Platform platform);

};

