#pragma once
#include "Enemy.h"

class Vampire1: public Enemy
{
public:
	Vampire1();
	~Vampire1();
	Vampire1(SDL_Renderer &renderer, glb::Vec2f spawnPoint, float scale);
	
	void update(float elapsedTime, Player &player);
	void draw(SDL_Renderer &renderer, float scale);
	void touchPlayer(Player* player);

	void setUpAnimations();
};

