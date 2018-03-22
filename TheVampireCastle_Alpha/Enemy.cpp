#include "Enemy.h"

#include "Player.h"


Enemy::Enemy() :
	_direction(glb::DOWN),
	_maxHealth(0),
	_currHealth(0),
	_knockBack(0),
	_c(0)
{
}


Enemy::~Enemy()
{
}


void Enemy::init(SDL_Renderer &renderer, std::string filePath, glb::Vec4i source, glb::Vec2f spawnPoint, float updateTime, float scale)
{
	AnimatedSprite::init(source, spawnPoint, filePath, renderer, updateTime, scale);
}


void Enemy::update(float elapsedTime, Player &player)
{
	AnimatedSprite::update(elapsedTime);
	
	if (_currHealth <= 0)
	{
		AnimatedSprite::setVisible(false);
		Rectangle tmp = this->_boundBox;
		this->_boundBox = Rectangle(0, 0, 0, 0);

		//Respawn
		if (_c++ == 200)
		{
			AnimatedSprite::setVisible(true);
			this->_boundBox = tmp;
			_currHealth = _maxHealth;
			_c = 0;
		}

	}
}


void Enemy::draw(SDL_Renderer &renderer, float scale)
{
	AnimatedSprite::draw(renderer, glb::Vec2i(_x, _y), scale);
}


void Enemy::gainHealth(int amount)
{
	if ((amount < 0 && _currHealth > 0) || (amount > 0 && _currHealth < _maxHealth))
		_currHealth += amount;
}