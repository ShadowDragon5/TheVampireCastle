#pragma once
#include <SDL\SDL.h>
#include "Globals.h"

class Tile
{
public:
	Tile();
	~Tile();
	Tile(SDL_Texture* tileset, glb::Vec2i size, glb::Vec2f tilesetPos, glb::Vec2f position, float scale);

	void update(float elapsedTime);
	void draw(SDL_Renderer &renderer, float scale);

private:
	SDL_Texture* _tileset;
	glb::Vec2i _size;
	glb::Vec2f _tilesetPos;
	glb::Vec2f _position;

};

