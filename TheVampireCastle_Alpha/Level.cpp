#include "Level.h"



Level::Level():
	_size(glb::Vec2i(0, 0))
{
}


Level::~Level()
{
}


void Level::init(std::string mapName, glb::Vec2i spawnPoint, SDL_Renderer &renderer)
{
	_mapName = mapName;
	_spawnPoint = spawnPoint;
	loadMap(mapName, renderer);
}


void Level::update(float elapsedTime)
{

}


void Level::draw(SDL_Renderer &renderer)
{

}


void Level::loadMap(std::string mapName, SDL_Renderer &renderer)
{

}