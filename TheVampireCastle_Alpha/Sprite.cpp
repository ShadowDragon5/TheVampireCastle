#include "Sprite.h"
#include "Errors.h"
#include "ResourceManager.h"

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}


void Sprite::init(glb::Vec4i source, glb::Vec2f pos, const std::string &filePath, SDL_Renderer &renderer)
{
	this->_x = pos.x;
	this->_y = pos.y;

	this->_srcRect.x = source.x;
	this->_srcRect.y = source.y;
	this->_srcRect.w = source.w;
	this->_srcRect.h = source.h;

	_spriteSheet = SDL_CreateTextureFromSurface(&renderer, ResourceManager::loadImage(filePath));
	if (_spriteSheet == NULL)
		fatalError("Failed to load image at:" + filePath);
}


void Sprite::update()
{

}


void Sprite::draw(SDL_Renderer &renderer, glb::Vec2i destination, float scale)
{
	SDL_Rect desRect = { destination.x, destination.y, _srcRect.w * scale, _srcRect.h * scale};
	SDL_RenderCopy(&renderer, _spriteSheet, &_srcRect, &desRect);
}