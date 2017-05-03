#pragma once

namespace glb
{
	const float scale = 3.0f;

	enum Direction
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
	
	struct Vec2f
	{
		float x;
		float y;

		Vec2f(float x, float y):
			x(x),
			y(y)
		{}

		Vec2f() :
			x(0),
			y(0)
		{}
	};
	
	struct Vec2i
	{
		int x;
		int y;

		Vec2i(int x, int y) :
			x(x),
			y(y)
		{}

		Vec2i():
			x(0),
			y(0)
		{}
	};

	struct Vec4i
	{
		int x, y;	//position
		int w;		//width
		int h;		//height

		Vec4i(int x, int y, int w, int h) :
			x(x),
			y(y),
			w(w),
			h(h)
		{}
	};
}