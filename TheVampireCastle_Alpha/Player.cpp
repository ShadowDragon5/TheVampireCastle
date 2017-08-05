#include "Player.h"
#include "ResourceManager.h"
#include "Enemy.h"

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
	_attack = -5;
	_attackBox = Rectangle(_x, _y + _boundBox.getHeight(), _boundBox.getWidth(), _boundBox.getHeight());
}


void Player::draw(SDL_Renderer &renderer, float scale)
{
	AnimatedSprite::draw(renderer, glb::Vec2i(_x, _y), scale);
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
		_x += _dx * elapsedTime / 1.41;
		_y += _dy * elapsedTime / 1.41;
	}

//Health regen
	static int time = 0;
	if ((this->_currHealth < _maxHealth) && (++time % 50 == 0))
	{
		gainHealth(1);
		time = 0;
	}

	switch (_facing)
	{
	case glb::UP:
		_attackBox = Rectangle(_x, _y - _boundBox.getHeight(), _boundBox.getWidth(), _boundBox.getHeight());
		break;
	case glb::DOWN:
		_attackBox = Rectangle(_x, _y + _boundBox.getHeight(), _boundBox.getWidth(), _boundBox.getHeight());
		break;
	case glb::LEFT:
		_attackBox = Rectangle(_x - _boundBox.getWidth(), _y, _boundBox.getWidth(), _boundBox.getHeight());
		break;
	case glb::RIGHT:
		_attackBox = Rectangle(_x + _boundBox.getWidth(), _y, _boundBox.getWidth(), _boundBox.getHeight());
		break;
	default:
		break;
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

	addAnimation("AttackDown", glb::Vec4i(48, 0, 16, 16), 1);
	addAnimation("AttackUp", glb::Vec4i(48, 16, 16, 16), 1);
	addAnimation("AttackRight", glb::Vec4i(48, 32, 16, 16), 1);
	addAnimation("AttackLeft", glb::Vec4i(48, 48, 16, 16), 1);
}

void Player::moveUp(bool movingX)
{
	_dy = -_speed;
	playAnimation("WalkUp");
	_facing = glb::UP;
	if (!movingX)
		_dx = 0.0f;
}


void Player::moveDown(bool movingX)
{
	_dy = _speed;
	playAnimation("WalkDown");
	_facing = glb::DOWN;
	if (!movingX)
		_dx = 0.0f;
}


void Player::moveRight(bool movingY)
{
	_dx = _speed;
	playAnimation("WalkRight");
	_facing = glb::RIGHT;
	if (!movingY)
		_dy = 0.0f;
}


void Player::moveLeft(bool movingY)
{
	_dx = -_speed;
	playAnimation("WalkLeft");
	_facing = glb::LEFT;
	if (!movingY)
		_dy = 0.0f;
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
				//_dy = 0;
				break;
			case glb::DOWN:
				_y = others[i].getTop() - 1 - _boundBox.getHeight();
				//_dy = 0;
				break;
			case glb::LEFT:
				_x = others[i].getRight() + 1;
				//_dx = 0;
				break;
			case glb::RIGHT:
				_x = others[i].getLeft() - _boundBox.getWidth() - 1;
				//_dx = 0;
				break;
			default:
				break;
			}
		}
	}
}


void Player::handleEnemyCollisions(std::vector<Enemy*> others)
{
	for (int i = 0; i < others.size(); i++)
	{
		others[i]->touchPlayer(this);

		glb::Direction collDir = Sprite::getCollDir(others[i]);
		if (collDir != glb::NONE)
		{
			switch (collDir)
			{
			case glb::UP:
				_y = others[i]->getBoundBox().getBottom() + others[i]->getKnockBack();
				//_dy = 0;
				break;
			case glb::DOWN:
				_y = others[i]->getBoundBox().getTop() - others[i]->getKnockBack() - _boundBox.getHeight();
				//_dy = 0;
				break;
			case glb::LEFT:
				_x = others[i]->getBoundBox().getRight() + others[i]->getKnockBack();
				//_dx = 0;
				break;
			case glb::RIGHT:
				_x = others[i]->getBoundBox().getLeft() - _boundBox.getWidth() - others[i]->getKnockBack();
				//_dx = 0;
				break;
			default:
				break;
			}
		}
	}
}


void Player::setAttackableEnemies(std::vector<Enemy*> enemies)
{
	_attackableEn = enemies;
}


void Player::gainHealth(int amount)
{
	if ((amount < 0 && _currHealth > 0) || (amount > 0 && _currHealth < _maxHealth))
		_currHealth += amount;
}


void Player::sprint(float amount)
{
		_speed = amount;
}


void Player::attack()
{
	switch (_facing)
	{
	case glb::UP:
		playAnimation("AttackUp");
		break;
	case glb::DOWN:
		playAnimation("AttackDown");
		break;
	case glb::LEFT:
		playAnimation("AttackLeft");
		break;
	case glb::RIGHT:
		playAnimation("AttackRight");
		break;
	default:
		break;
	}
	for (int i = 0; i < _attackableEn.size(); i++)
	{
		_attackableEn[i]->gainHealth(_attack);
	}
}