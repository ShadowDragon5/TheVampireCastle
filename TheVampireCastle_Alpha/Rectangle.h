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

	inline int getLeft() const { return _x; }
	inline int getRight() const { return _x + _width; }
	inline int getTop() const { return _y; }
	inline int getBottom() const { return _y + _height; }

	inline int getSide(glb::Direction dir)
	{
		return
			dir == glb::LEFT ? getLeft() :
			dir == glb::RIGHT ? getRight() :
			dir == glb::UP ? getTop() :
			dir == glb::DOWN ? getBottom() :
			glb::NONE;
	}

	inline bool collidesWith(const Rectangle &other)
	{
		return
			getRight() >= other.getLeft() &&
			getLeft() <= other.getRight() &&
			getTop() <= other.getBottom() &&
			getBottom() >= other.getTop();
	}

	inline bool isValidRectangle()
	{
		return (_x >= 0 && _y >= 0 && _width >= 0 && _height >= 0);
	}

	inline int getWidth() { return _width; }
	inline int getHeight() { return _height; }

//set
	inline void setX(int x) { _x = x; }
	inline void setY(int y) { _y = y; }
	inline void setWidth(int width) { _width = width; }
	inline void setHeight(int height) { _height = height; }

private:
	int _x, _y, _width, _height;

};

