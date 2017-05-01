#pragma once

namespace glb
{
	const float scale = 4.0f;

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
	};

	struct Vec2i
	{
		int x;
		int y;

		Vec2i(int x, int y) :
			x(x),
			y(y)
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