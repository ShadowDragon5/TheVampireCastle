#include "Player.h"
#include "ResourceManager.h"


Player::Player():
	_dx(0.0f),
	_dy(0.0f),
	_maxHealth(10),
	_currHealth(_maxHealth)
{
}


Player::~Player()
{
}


void Player::init(SDL_Renderer &renderer, glb::Vec2f pos, float scale)
{
	AnimatedSprite::init(glb::Vec4i(0, 0, 16, 16), pos, "content/sprites/Player.png", renderer, 200, scale);
	ResourceManager::loadImage("content/sprites/Player.png");

	setUpAnimations();
	_facing = glb::DOWN;
}


void Player::draw(SDL_Renderer &renderer, float scale)
{
	AnimatedSprite::draw(renderer, glb::Vec2i(_x, _y), scale);
	_speed = scale / 15.0f;
}


void Player::update(float elapsedTime)
{
	if (_dx == 0 || _dy == 0)
	{
		_x += _dx * elapsedTime;
		_y += _dy * elapsedTime;
	}
	else
	{
		_x += _dx * elapsedTime / 1.4;
		_y += _dy * elapsedTime / 1.4;
	}

	AnimatedSprite::update(elapsedTime);
}


void Player::setUpAnimations()
{
	addAnimation("WalkDown", glb::Vec4i(16, 0, 16, 16), 2);
	addAnimation("WalkUp", glb::Vec4i(16, 16, 16, 16), 2);
	addAnimation("WalkRight", glb::Vec4i(16, 32, 16, 16), 2);
	addAnimation("WalkLeft", glb::Vec4i(16, 48, 16, 16), 2);

	addAnimation("IdleDown", glb::Vec4i(0, 0, 16, 16), 1);
	addAnimation("IdleUp", glb::Vec4i(0, 16, 16, 16), 1);
	addAnimation("IdleRight", glb::Vec4i(0, 32, 16, 16), 1);
	addAnimation("IdleLeft", glb::Vec4i(0, 48, 16, 16), 1);
}

void Player::moveUp()
{
	_dy = -_speed;
	playAnimation("WalkUp");
	_facing = glb::UP;
}


void Player::moveDown()
{
	_dy = _speed;
	playAnimation("WalkDown");
	_facing = glb::DOWN;
}


void Player::moveRight()
{
	_dx = _speed;
	playAnimation("WalkRight");
	_facing = glb::RIGHT;
}


void Player::moveLeft()
{
	_dx = -_speed;
	playAnimation("WalkLeft");
	_facing = glb::LEFT;
}


void Player::stopMoving()
{
	_dx = 0.0f;
	_dy = 0.0f;

	switch (_facing)
	{
	case glb::LEFT:
		playAnimation("IdleLeft");
		break;
	case glb::RIGHT:
		playAnimation("IdleRight");
		break;
	case glb::UP:
		playAnimation("IdleUp");
		break;
	case glb::DOWN:
		playAnimation("IdleDown");
		break;
	default:
		break;
	}
}


void Player::handleTileCollisions(std::vector<Rectangle> &others)
{
	for (int i = 0; i < others.size(); i++)
	{
		glb::Direction collDir = Sprite::getCollDir(others[i]);
		if (collDir != glb::NONE)
		{
			switch (collDir)
			{
			case glb::UP:
				_y = others[i].getBottom() + 1;
				_dy = 0;
				break;
			case glb::DOWN:
				_y = others[i].getTop() - 1 - _boundBox.getHeight();
				_dy = 0;
				break;
			case glb::LEFT:
				_x = others[i].getRight() + 1;
				_dx = 0;
				break;
			case glb::RIGHT:
				_x = others[i].getLeft() - _boundBox.getWidth() - 1;
				_dx = 0;
				break;
			default:
				break;
			}
		}
	}
}