#include "Game.h"

Game::Game():
	_window(nullptr),
	_renderer(nullptr),
	_screenWidth(1280),
	_screenHeight(720),
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
	
	//Inicializuojami zaidimo elementai
	_level.init("TestRoom", glb::Vec2f(100, 100), *_renderer, _scale);
	_player.init(*_renderer, _level.getPlayerSpawnPoint(), _scale);
	_hud.init(*_renderer, _player, _scale);

	gameLoop();
}

//Inicializuojamos sistemos naudojamos zaidime
void Game::initSystems()
{
	// Inicializuojami visi SDL parametrai
	SDL_Init(SDL_INIT_EVERYTHING);

	//Sukuriamas langas
	SDL_CreateWindowAndRenderer(
		_screenWidth,
		_screenHeight,
		0,
		&_window,
		&_renderer);

	//Nustatomas lango pavadinimas
	SDL_SetWindowTitle(_window, "The Vampire Castle");

	//Nustato fono spalva
	SDL_SetRenderDrawColor(_renderer, 64, 64, 64, 255);
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
			//system("cls");
			std::printf("%f\n", _fps);
			i = 0;
		}
		
		//Apriboja FPS iki maxFPS
		float frameTicks = SDL_GetTicks() - startTicks;
		if (1000.0f / _maxFPS > frameTicks)
			SDL_Delay(1000.0f / _maxFPS - frameTicks);

		update(1000.0f / _maxFPS);
	}
}

//Apdoroja ivesties duomenis
void Game::processInput()
{
	SDL_Event evnt;

	if (SDL_PollEvent(&evnt))
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
		case SDL_MOUSEBUTTONDOWN:
			_player.attack();
			break;
		default:
			break;
		}
		if (_input.isKeyPressed(SDL_SCANCODE_ESCAPE))
			_gameState = GameState::EXIT;

		//Begimas
		if (_input.isKeyHeld(SDL_SCANCODE_LSHIFT))
			_player.sprint(0.3f);
		else
			_player.sprint(glb::scale / 15.0f);

		if (_input.isKeyHeld(SDL_SCANCODE_W) || _input.isKeyHeld(SDL_SCANCODE_UP))
			_player.moveUp(_input.isKeyHeld(SDL_SCANCODE_D) || _input.isKeyHeld(SDL_SCANCODE_RIGHT) || _input.isKeyHeld(SDL_SCANCODE_A) || _input.isKeyHeld(SDL_SCANCODE_LEFT));
		if (_input.isKeyHeld(SDL_SCANCODE_S) || _input.isKeyHeld(SDL_SCANCODE_DOWN))
			_player.moveDown(_input.isKeyHeld(SDL_SCANCODE_D) || _input.isKeyHeld(SDL_SCANCODE_RIGHT) || _input.isKeyHeld(SDL_SCANCODE_A) || _input.isKeyHeld(SDL_SCANCODE_LEFT));
		if (_input.isKeyHeld(SDL_SCANCODE_D) || _input.isKeyHeld(SDL_SCANCODE_RIGHT))
			_player.moveRight(_input.isKeyHeld(SDL_SCANCODE_W) || _input.isKeyHeld(SDL_SCANCODE_UP) || _input.isKeyHeld(SDL_SCANCODE_S) || _input.isKeyHeld(SDL_SCANCODE_DOWN));
		if (_input.isKeyHeld(SDL_SCANCODE_A) || _input.isKeyHeld(SDL_SCANCODE_LEFT))
			_player.moveLeft(_input.isKeyHeld(SDL_SCANCODE_W) || _input.isKeyHeld(SDL_SCANCODE_UP) || _input.isKeyHeld(SDL_SCANCODE_S) || _input.isKeyHeld(SDL_SCANCODE_DOWN));
		if (!_input.isKeyHeld(SDL_SCANCODE_W) && !_input.isKeyHeld(SDL_SCANCODE_S)
			&& !_input.isKeyHeld(SDL_SCANCODE_D) && !_input.isKeyHeld(SDL_SCANCODE_A)
			&& !_input.isKeyHeld(SDL_SCANCODE_UP) && !_input.isKeyHeld(SDL_SCANCODE_DOWN)
			&& !_input.isKeyHeld(SDL_SCANCODE_RIGHT) && !_input.isKeyHeld(SDL_SCANCODE_LEFT))
			_player.stopMoving();
	}
}


void Game::drawGame()
{
	SDL_RenderClear(_renderer);
	
	_level.draw(*_renderer, _scale);
	_player.draw(*_renderer, _scale);

	_hud.draw(*_renderer, _scale);

	SDL_RenderPresent(_renderer);
}


void Game::update(float elapsedTime)
{
	_level.update(elapsedTime, _player);
	_player.update(elapsedTime);
	_hud.update(elapsedTime, _player);

	std::vector<Rectangle> others;
	if ((others = _level.checkTileCollisions(_player.getBoundBox())).size() > 0)
	{
		_player.handleTileCollisions(others);
	}

	std::vector<Enemy*> otherEn;
	if ((otherEn = _level.checkEnemyCollisions(_player.getBoundBox())).size() > 0)
		_player.handleEnemyCollisions(otherEn);

	if ((otherEn = _level.checkEnemyCollisions(_player.getAttackBox())).size() > 0)
		_player.setAttackableEnemies(otherEn);
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

