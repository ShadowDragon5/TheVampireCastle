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
	_healthBar.init(glb::Vec4i(0, 0, 96, 22), glb::Vec2f(50.0f / 3 * scale, 60.0f / 3 * scale), "content/sprites/hud.png", renderer, scale);
	_healthNum1.init(glb::Vec4i(0, 22, 8, 8), glb::Vec2f(50.0f / 3 * scale, 102.0f / 3 * scale), "content/sprites/hud.png", renderer, scale);
	_healthNum2.init(glb::Vec4i(0, 22, 8, 8), glb::Vec2f(70.0f / 3 * scale, 102.0f / 3 * scale), "content/sprites/hud.png", renderer, scale);
	_healthCurrBar.init(glb::Vec4i(96, 0, 96, 12), glb::Vec2f(50.0f / 3 * scale, 60.0f / 3 * scale), "content/sprites/hud.png", renderer, scale);
}


void HUD::update(float elapsedTime, Player &player)
{
	*_player = player;
	_healthNum1.setSrcRectX(_player->getCurrHealth() / 10 % 10 * 8 == 0 ? 80 : _player->getCurrHealth() / 10 % 10 * 8);
	_healthNum2.setSrcRectX(_player->getCurrHealth() % 10 * 8);
	_healthCurrBar.setSrcRectW(96 * _player->getCurrHealth() / _player->getMaxHealth());
}


void HUD::draw(SDL_Renderer &renderer, float scale)
{
	_healthCurrBar.draw(renderer, glb::Vec2i(_healthCurrBar.getX(), _healthCurrBar.getY()), scale);
	_healthBar.draw(renderer, glb::Vec2i(_healthBar.getX(), _healthBar.getY()), scale);
	_healthNum1.draw(renderer, glb::Vec2i(_healthNum1.getX(), _healthNum1.getY()), scale);
	_healthNum2.draw(renderer, glb::Vec2i(_healthNum2.getX(), _healthNum2.getY()), scale);
}