#pragma once
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>

#include "Input.h"
#include "Player.h"
#include "Level.h"
#include "HUD.h"

enum GameState
{
	PLAY,
	EXIT
};

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	void initSystems();
	void gameLoop();
	void processInput();
	void drawGame();
	void update(float elapsedTime);

	void calculateFPS();

	SDL_Window* _window;		//window pointer
	SDL_Renderer* _renderer;

	int _screenWidth;			//window width
	int _screenHeight;			//window height
	float _scale;

	GameState _gameState;
	Input _input;

	float _fps;					//frames per second
	float _maxFPS;				//maximum frames per second

	Player _player;
	Level _level;
	HUD _hud;
};

