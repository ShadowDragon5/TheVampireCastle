#include "Sprite.h"
#include "Errors.h"
#include "ResourceManager.h"

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}


void Sprite::init(glb::Vec4i source, glb::Vec2f pos, const std::string &filePath, SDL_Renderer &renderer, float scale)
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

	_scale = scale;
	_boundBox = Rectangle(_x, _y, source.w * scale, source.h * scale);
}


void Sprite::update()
{
	_boundBox = Rectangle(_x, _y, _srcRect.w * _scale, _srcRect.h * _scale);
}


void Sprite::draw(SDL_Renderer &renderer, glb::Vec2i destination, float scale)
{
	_scale = scale;
	SDL_Rect desRect = { destination.x, destination.y, _srcRect.w * scale, _srcRect.h * scale};
	SDL_RenderCopy(&renderer, _spriteSheet, &_srcRect, &desRect);
}


glb::Direction Sprite::getCollDir(Rectangle &other) const
{
	int amtRight, amtLeft, amtTop, amtBottom;
	amtRight = getBoundBox().getRight() - other.getLeft();
	amtLeft = other.getRight() - getBoundBox().getLeft();
	amtTop = other.getBottom() - getBoundBox().getTop();
	amtBottom = getBoundBox().getBottom() - other.getTop();

	int vals[4] = { abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom) };
	int lowest = vals[0];
	for (int i = 0; i < 4; i++) {
		if (vals[i] < lowest) {
			lowest = vals[i];
		}
	}

	return
		lowest == abs(amtRight) ? glb::RIGHT :
		lowest == abs(amtLeft) ? glb::LEFT :
		lowest == abs(amtTop) ? glb::UP :
		lowest == abs(amtBottom) ? glb::DOWN :
		glb::NONE;

}