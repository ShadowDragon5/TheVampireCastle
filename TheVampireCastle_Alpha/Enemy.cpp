#include "Enemy.h"



Enemy::Enemy() :
	_direction(glb::DOWN),
	_maxHealth(0),
	_currHealth(0)
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
}


void Enemy::draw(SDL_Renderer &renderer, float scale)
{
	AnimatedSprite::draw(renderer, glb::Vec2i(_x, _y), scale);
}