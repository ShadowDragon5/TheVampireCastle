#include "AnimatedSprite.h"

#include "Sprite.h"


AnimatedSprite::AnimatedSprite():
	_frameIndex(0),
	_visible(true),
	_curAnim("")
{
}


AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::init(glb::Vec4i source, glb::Vec2f pos, const std::string &filePath, SDL_Renderer &renderer, float updateTime, float scale)
{
	Sprite::init(source, pos, filePath, renderer, scale);
	this->_timeToUpdate = updateTime;
}

void AnimatedSprite::playAnimation(std::string animation, bool once)
{
	_once = once;
	if (_curAnim != animation)
	{
		_curAnim = animation;
		_frameIndex = 0;
	}
}

void AnimatedSprite::update(float elapsedTime)
{
	Sprite::update();

	_time += elapsedTime;
	if (_time > _timeToUpdate)
	{
		_time -= _timeToUpdate;
		if (_frameIndex < _animations[_curAnim].size() - 1)
			_frameIndex++;
		else
		{
			if (_once)
				setVisible(false);

			_frameIndex = 0;

			//animationDone
		}
	}
}

void AnimatedSprite::draw(SDL_Renderer &renderer, glb::Vec2i destination, float scale)
{
	if (_visible)
	{
		SDL_Rect desRect = { destination.x, destination.y, _srcRect.w * scale, _srcRect.h * scale };
		SDL_Rect srceRect = _animations[_curAnim][_frameIndex];
		SDL_RenderCopy(&renderer, _spriteSheet, &srceRect, &desRect);
	}
}

void AnimatedSprite::addAnimation(std::string name, glb::Vec4i src, int frames)
{
	std::vector<SDL_Rect> rectangles;
	for (int i = 0; i < frames; i++)
		rectangles.push_back(SDL_Rect() = { i * src.w + src.x, src.y, src.w, src.h });

	_animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));

	rectangles.clear();
}

void AnimatedSprite::resetAnimations()
{
	_animations.clear();
}


void AnimatedSprite::stopAnimation()
{
	_frameIndex = 0;
	//animationDone
}