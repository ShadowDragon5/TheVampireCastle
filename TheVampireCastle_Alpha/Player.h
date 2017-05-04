#pragma once
#include <SDL\SDL.h>
#include "AnimatedSprite.h"
#include "Globals.h"
#include <vector>

class Enemy;

class Player: public AnimatedSprite
{
public:
	Player();
	~Player();

	void init(SDL_Renderer &renderer, glb::Vec2f pos, float scale);
	void draw(SDL_Renderer &renderer, float scale);
	void update(float elapsedTime);

//movement functions
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void stopMoving();

	virtual void setUpAnimations();
	void handleTileCollisions(std::vector<Rectangle> &others);
	void handleEnemyCollisions(std::vector<Enemy*> others);

	void gainHealth(int amount);
//get
	inline int getMaxHealth() { return _maxHealth; }
	inline int getCurrHealth() { return _currHealth; }

private:
	float _dx, _dy;
	glb::Direction _facing;
	float _speed = glb::scale / 15.0f;

	int _maxHealth;
	int _currHealth;
};

