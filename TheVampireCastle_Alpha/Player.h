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

//Moving functions
	void moveUp(bool movingX);
	void moveDown(bool movingX);
	void moveRight(bool movingX);
	void moveLeft(bool movingY);
	void stopMoving();

	virtual void setUpAnimations();
	void handleTileCollisions(std::vector<Rectangle> &others);
	void handleEnemyCollisions(std::vector<Enemy*> others);
	void setAttackableEnemies(std::vector<Enemy*> enemies);

	void gainHealth(int amount);
	void sprint(float amount);
	void attack();

//get
	inline int getMaxHealth() { return _maxHealth; }
	inline int getCurrHealth() { return _currHealth; }
	inline Rectangle getAttackBox() { return _attackBox; }

private:
	float _dx, _dy;						//
	glb::Direction _facing;				//Side player is facing
	float _speed = glb::scale / 15.0f;	//Player speed

	int _maxHealth;
	int _currHealth;
	int _attack;						//Attack dammage
	Rectangle _attackBox;				//Area of attack
	std::vector<Enemy*> _attackableEn;	//Vector of attackable enemies
};

