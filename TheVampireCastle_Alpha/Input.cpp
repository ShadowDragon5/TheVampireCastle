#include "Input.h"


Input::Input()
{
}


Input::~Input()
{
}


void Input::beginNewFrame()
{
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
}


void Input::keyUpEvent(const SDL_Event &evnt)
{
	SDL_Scancode scanCode = evnt.key.keysym.scancode;
	this->_releasedKeys[scanCode] = true;
	this->_heldKeys[scanCode] = false;
}


void Input::keyDownEvent(const SDL_Event &evnt)
{
	SDL_Scancode scanCode = evnt.key.keysym.scancode;
	this->_pressedKeys[scanCode] = true;
	this->_heldKeys[scanCode] = true;
}


bool Input::isKeyPressed(SDL_Scancode key)
{
	return _pressedKeys[key];
}


bool Input::isKeyReleased(SDL_Scancode key)
{
	return _releasedKeys[key];
}


bool Input::isKeyHeld(SDL_Scancode key)
{
	return _heldKeys[key];
}