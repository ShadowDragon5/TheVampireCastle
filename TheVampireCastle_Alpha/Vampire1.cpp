#include "Vampire1.h"
#include "Player.h"

Vampire1::Vampire1()
{
}


Vampire1::Vampire1(SDL_Renderer &renderer, glb::Vec2f spawnPoint, float scale)
{
	Enemy::init(renderer, "content/sprites/vampire1.png", glb::Vec4i(0, 0, 16, 16), spawnPoint, 140, scale);
	setUpAnimations();
	playAnimation("IdleDown");
	_maxHealth = 10;
	_currHealth = _maxHealth;
	_knockBack = 50 / 3 * scale;
}


Vampire1::~Vampire1()
{
}


void Vampire1::update(float elapsedTime, Player &player)
{
	Enemy::update(elapsedTime, player);
}


void Vampire1::draw(SDL_Renderer &renderer, float scale)
{

	Enemy::draw(renderer, scale);
}


void Vampire1::setUpAnimations()
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


void Vampire1::touchPlayer(Player* player)
{
	player->gainHealth(-1);
}