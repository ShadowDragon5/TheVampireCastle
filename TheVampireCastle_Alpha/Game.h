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

	SDL_Window* _window;		//Lango rodykle
	SDL_Renderer* _renderer;

	int _screenWidth;			//Lango plotis
	int _screenHeight;			//Lango aukstis
	float _scale;

	GameState _gameState;		//Zaidimo busena
	Input _input;

	float _fps;					//Kadrai per sekunde
	float _maxFPS;				//Daugiausia leidziamu kadru per sekunde

	Player _player;
	Level _level;
	HUD _hud;
};

