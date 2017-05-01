#pragma once
#include <string>
#include <SDL\SDL.h>
#include "Globals.h"

class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	void init(glb::Vec4i source, glb::Vec2f pos, const std::string &filePath, SDL_Renderer &renderer);

	virtual void update();

	void draw(SDL_Renderer &renderer, glb::Vec2i destination);

protected:
	SDL_Rect _srcRect;
	SDL_Texture* _spriteSheet;
	float _x, _y;					//Position
};

