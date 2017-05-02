#pragma once
#include <string>
#include "Globals.h"
#include <SDL\SDL.h>

class Level
{
public:
	Level();
	~Level();

	void init(std::string mapName, glb::Vec2i spawnPoint, SDL_Renderer &renderer);
	void update(float elapsedTime);
	void draw(SDL_Renderer &renderer);

private:
	void loadMap(std::string mapName, SDL_Renderer &renderer);

	std::string _mapName;
	glb::Vec2i _spawnPoint;
	glb::Vec2i _size;
};

