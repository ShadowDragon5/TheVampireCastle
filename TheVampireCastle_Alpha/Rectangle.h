#pragma once
#include "Globals.h"

class Rectangle
{
public:
	Rectangle() {}
	~Rectangle() {}

	Rectangle(int x, int y, int width, int height):
		_x(x),
		_y(y),
		_width(width),
		_height(height)
	{}

	inline int getCenterX() { return _x + _width / 2; }
	inline int getCenterY() { return _y + _height / 2; }

	inline int getLeft() { return _x; }
	inline int getRight() { return _x + _width; }
	inline int getTop() { return _y; }
	inline int getBottom() { return _y + _height; }

	inline int getSide(glb::Direction dir)
	{
		return
			dir == glb::LEFT ? getLeft() :
			dir == glb::RIGHT ? getRight() :
			dir == glb::UP ? getTop() :
			dir == glb::DOWN ? getBottom() :
			glb::NONE;
	}

	bool collidesWith(Rectangle &other)
	{
		return
			getRight() >= other.getLeft() &&
			getLeft() <= other.getRight() &&
			getTop() <= other.getBottom() &&
			getBottom() >= other.getTop();
	}

	bool isValidRectangle()
	{
		return (_x >= 0 && _y >= 0 && _width >= 0 && _height >= 0);
	}

private:
	int _x, _y, _width, _height;

};

