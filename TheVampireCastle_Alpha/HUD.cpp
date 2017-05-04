#include "HUD.h"
#include "Globals.h"


HUD::HUD()
{
}


HUD::~HUD()
{
}


void HUD::init(SDL_Renderer &renderer, Player &player, float scale)
{
	_player = &player;
	_healthBar.init(glb::Vec4i(0, 0, 64, 8), glb::Vec2f(35.0f, 70.0f), "content/sprites/hud.png", renderer, scale);
	_healthNum1.init(glb::Vec4i(0, 8, 8, 8), glb::Vec2f(66.0f, 90.0f), "content/sprites/hud.png", renderer, scale);
	_healthCurrBar.init(glb::Vec4i(64, 0, 64, 8), glb::Vec2f(35.0f, 70.0f), "content/sprites/hud.png", renderer, scale);
}


void HUD::update(float elapsedTime, Player &player)
{
	*_player = player;
	_healthNum1.setSrcRectX(8 * _player->getCurrHealth());
	_healthCurrBar.setSrcRectW(64 * _player->getCurrHealth() / _player->getMaxHealth());
}


void HUD::draw(SDL_Renderer &renderer, float scale)
{
	_healthBar.draw(renderer, glb::Vec2i(_healthBar.getX(), _healthBar.getY()), scale);
	_healthNum1.draw(renderer, glb::Vec2i(_healthNum1.getX(), _healthNum1.getY()), scale);
	_healthCurrBar.draw(renderer, glb::Vec2i(_healthCurrBar.getX(), _healthCurrBar.getY()), scale);
}