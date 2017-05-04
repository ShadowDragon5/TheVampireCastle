#pragma once
#include <SDL\SDL.h>
#include "Player.h"


class HUD
{
public:
	HUD();
	~HUD();

	void init(SDL_Renderer &renderer, Player &player, float scale);
	void update(float elapsedTime, Player &player);
	void draw(SDL_Renderer &renderer, float scale);

private:
	Player* _player;

	Sprite _healthBar;
	Sprite _healthNum1;
	Sprite _healthCurrBar;

};

