#pragma once
#include <SDL\SDL.h>
#include "AnimatedSprite.h"
#include "Globals.h"

class Player: public AnimatedSprite
{
public:
	Player();
	~Player();

	void init(SDL_Renderer &renderer, glb::Vec2f pos);
	void draw(SDL_Renderer &renderer);
	void update(float elapsedTime);

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void stopMoving();

	virtual void setUpAnimations();
private:
	float _dx, _dy;

	glb::Direction _facing;

	const float _speed = glb::scale / 20;
};

