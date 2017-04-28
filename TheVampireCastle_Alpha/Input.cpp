#include "Input.h"


Input::Input()
{
}


Input::~Input()
{
}

//Isvalo paspaustu ir paleistu mygtuku map'us
void Input::beginNewFrame()
{
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
}

//Nustato kad mygtukas buvo paleistas
void Input::keyUpEvent(const SDL_Event &evnt)
{
	SDL_Scancode scanCode = evnt.key.keysym.scancode;
	this->_releasedKeys[scanCode] = true;
	this->_heldKeys[scanCode] = false;
}

//Nustato kad mygtukas buvo paspaustas
void Input::keyDownEvent(const SDL_Event &evnt)
{
	SDL_Scancode scanCode = evnt.key.keysym.scancode;
	this->_pressedKeys[scanCode] = true;
	this->_heldKeys[scanCode] = true;
}

//Grazina ar tas mygtukas yra paspaustas
bool Input::isKeyPressed(SDL_Scancode key)
{
	return _pressedKeys[key];
}

//Grazina ar tas mygtukas yra paleistas
bool Input::isKeyReleased(SDL_Scancode key)
{
	return _releasedKeys[key];
}

//Grazina ar tas mygtukas yra laikomas
bool Input::isKeyHeld(SDL_Scancode key)
{
	return _heldKeys[key];
}