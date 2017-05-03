#include "Game.h"

#include <iostream>

Game::Game():
	_window(nullptr),
	_renderer(nullptr),
	_screenWidth(854),
	_screenHeight(480),
	_maxFPS(60.0f),
	_scale(glb::scale)
{
}


Game::~Game()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
}


void Game::run()
{
	initSystems();
	


	_level.init("TestRoom", glb::Vec2f(100, 100), *_renderer, _scale);
	_player.init(*_renderer, _level.getPlayerSpawnPoint(), _scale);
	_hud.init(*_renderer, _player, _scale);

	gameLoop();
}

//Inicializuojamos sistemos naudojamos zaidime
void Game::initSystems()
{
	// Inicializuojami visi SDL parametrai
	SDL_Init(SDL_INIT_EVERYTHING);	//TODO: remove not needed flags

	//Creating Window
	SDL_CreateWindowAndRenderer(
		_screenWidth,
		_screenHeight,
		0 |						//Flags
		SDL_WINDOW_RESIZABLE,
		&_window,
		&_renderer);

	SDL_SetWindowTitle(_window, "The Vampire Castle");

	//Sets background color
	SDL_SetRenderDrawColor(_renderer, 150, 0, 255, 255);
}

//Zaidimo ciklas
void Game::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		float startTicks = SDL_GetTicks();

		_input.beginNewFrame();
		processInput();

		drawGame();


		//for debug
		
		calculateFPS();
		static int i = 0;
		if (++i % 100 == 0)
		{
			system("cls");
			std::cout << _fps << std::endl;
			i = 0;
		}
		
		float frameTicks = SDL_GetTicks() - startTicks;
		update(frameTicks < _maxFPS ? frameTicks : _maxFPS);

		//Apriboja FPS iki maxFPS
		//if (1000.0f / _maxFPS > frameTicks)
		//	SDL_Delay(1000.0f / _maxFPS - frameTicks);
	}
}

//Apdoroja ivesties duomenis
void Game::processInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			if (!evnt.key.repeat)
				_input.keyDownEvent(evnt);
			break;
		case SDL_KEYUP:
			_input.keyUpEvent(evnt);
			break;
		default:
			break;
		}
		//TODO: fix diaginal movement
		if (_input.isKeyPressed(SDL_SCANCODE_ESCAPE))
			_gameState = GameState::EXIT;
		else if (_input.isKeyHeld(SDL_SCANCODE_W))
			_player.moveUp();
		else if (_input.isKeyHeld(SDL_SCANCODE_S))
			_player.moveDown();
		else if (_input.isKeyHeld(SDL_SCANCODE_D))
			_player.moveRight();
		else if (_input.isKeyHeld(SDL_SCANCODE_A))
			_player.moveLeft();
		else if (!_input.isKeyHeld(SDL_SCANCODE_W) && !_input.isKeyHeld(SDL_SCANCODE_S)
			&& !_input.isKeyHeld(SDL_SCANCODE_D) && !_input.isKeyHeld(SDL_SCANCODE_A))
			_player.stopMoving();
	}
}


void Game::drawGame()
{
	SDL_RenderClear(_renderer);

	//Nuskaito lango dydi ir pakeicia piesiamu objektu dydi pagal tai
	/*
	int h;
	SDL_GetWindowSize(_window, nullptr, &h);
	_scale = h * 3.0f / 480;
	*/

	//TODO::recalculate tile postition for scaling
	_level.draw(*_renderer, _scale);
	_player.draw(*_renderer, _scale);

	_hud.draw(*_renderer, _scale);

	SDL_RenderPresent(_renderer);
}


void Game::update(float elapsedTime)
{
	_level.update(elapsedTime, _player);
	_player.update(elapsedTime);
	_hud.update(elapsedTime);

	std::vector<Rectangle> others;
	if ((others = _level.checkTileColisions(_player.getBoundBox())).size() > 0)
	{
		_player.handleTileCollisions(others);
	}
}

//Skaiciuoja kadrus per sekunde
void Game::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();
	float currentTicks;

	currentTicks = SDL_GetTicks();

	frameTimes[currentFrame % NUM_SAMPLES] = currentTicks - prevTicks;

	prevTicks = currentTicks;

	int count;

	if (++currentFrame < NUM_SAMPLES)
		count = currentFrame;
	else
		count = NUM_SAMPLES;

	float frameTimeAverage = 0;

	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
		_fps = 1000.0f / frameTimeAverage;
	else
		_fps = -1.0f;
}

