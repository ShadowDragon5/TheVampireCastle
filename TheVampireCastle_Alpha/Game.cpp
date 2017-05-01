#include "Game.h"

#include <iostream>

Game::Game():
	_window(nullptr),
	_renderer(nullptr),
	_screenWidth(854),
	_screenHeight(480),
	_maxFPS(60.0f)
{
}


Game::~Game()
{
}


void Game::run()
{
	initSystems();

	_player.init(glb::Vec4i(0, 0, 16, 16), glb::Vec2f(100.0f, 100.0f), "Textures/Player.png", *_renderer, 25);
	_player.setUpAnimations();

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

}

//Zaidimo ciklas
void Game::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		float startTicks = SDL_GetTicks();

		_input.beginNewFrame();


		processInput();

		//draw Game

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
		if (1000.0f / _maxFPS > frameTicks)
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
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
		if (_input.isKeyPressed(SDL_SCANCODE_ESCAPE))
			_gameState = GameState::EXIT;
	}
}


void Game::drawGame()
{
	SDL_RenderClear(_renderer);

	_player.playAnimation("WalkForward");
	_player.draw(*_renderer, glb::Vec2i(100, 100));

	SDL_RenderPresent(_renderer);
}


void Game::update(float elapsedTime)
{
	_player.update(elapsedTime);
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

