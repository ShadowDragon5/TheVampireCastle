#include "Tile.h"


Tile::Tile()
{
}


Tile::~Tile()
{
}


Tile::Tile(SDL_Texture* tileset, glb::Vec2i size, glb::Vec2f tilesetPos, glb::Vec2f position, float scale):
	_tileset(tileset),
	_size(size),
	_tilesetPos(tilesetPos),
	_position(glb::Vec2f(position.x * scale, position.y * scale))
{
}


void Tile::update(float elapsedTime)
{

}


void Tile::draw(SDL_Renderer &renderer, float scale)
{
	SDL_Rect desRect = { _position.x, _position.y, _size.x * scale, _size.y * scale };
	SDL_Rect srcRect = { _tilesetPos.x, _tilesetPos.y, _size.x, _size.y };

	SDL_RenderCopy(&renderer, _tileset, &srcRect, &desRect);
}