#pragma once
#include <string>
#include <SDL\SDL.h>
#include "Globals.h"
#include "Rectangle.h"

class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	void init(glb::Vec4i source, glb::Vec2f pos, const std::string &filePath, SDL_Renderer &renderer, float scale);
	virtual void update();
	void draw(SDL_Renderer &renderer, glb::Vec2i destination, float scale);

	inline Rectangle getBoundBox() const { return _boundBox; }
	glb::Direction getCollDir(Rectangle &other) const;

//get
	inline float getX() { return _x; }
	inline float getY() { return _y; }

//set
	inline void setSrcRectX(int x) { _srcRect.x = x; }
	inline void setSrcRectY(int y) { _srcRect.y = y; }


protected:
	SDL_Rect _srcRect;
	SDL_Texture* _spriteSheet;
	float _x, _y;					//Position
	float _scale;

	Rectangle _boundBox;
};

