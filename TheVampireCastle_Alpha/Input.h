#pragma once
#include <SDL\SDL.h>
#include <map>

//TODO: add MOUSE input

class Input
{
public:
	Input();
	~Input();

	void beginNewFrame();
	void keyUpEvent(const SDL_Event &evnt);
	void keyDownEvent(const SDL_Event &evnt);

	bool isKeyPressed(SDL_Scancode key);
	bool isKeyReleased(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);

private:
	std::map<SDL_Scancode, bool> _heldKeys;
	std::map<SDL_Scancode, bool> _pressedKeys;
	std::map<SDL_Scancode, bool> _releasedKeys;
};

