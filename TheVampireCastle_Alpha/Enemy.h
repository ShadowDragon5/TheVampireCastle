#pragma once
#include <SDL\SDL.h>
#include <string>

#include "AnimatedSprite.h"
#include "Globals.h"

class Player;

class Enemy: public AnimatedSprite
{
public:
	Enemy();
	~Enemy();

	void init(SDL_Renderer &renderer, std::string filePath, glb::Vec4i source, glb::Vec2f spawnPoint, float updateTime, float scale);
	virtual void update(float elapsedTime, Player &player);
	virtual void draw(SDL_Renderer &renderer, float scale);
	virtual void touchPlayer(Player *player) = 0;
	void gainHealth(int amount);

//Get
	inline int getMaxHealth() { return _maxHealth; }
	inline int getCurrHealth() { return _currHealth; }
	inline int getKnockBack() { return _knockBack; }

protected:
	glb::Direction _direction;

	int _maxHealth;
	int _currHealth;

	int _knockBack;

};

