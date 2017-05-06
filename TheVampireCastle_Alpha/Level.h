#pragma once
#include <string>
#include <SDL\SDL.h>
#include <vector>

#include "Globals.h"
#include "Tile.h"
#include "Rectangle.h"
#include "Enemy.h"

struct Tileset;

class Level
{
public:
	Level();
	~Level();

	void init(std::string mapName, glb::Vec2f spawnPoint, SDL_Renderer &renderer, float scale);
	void update(float elapsedTime, Player &player);
	void draw(SDL_Renderer &renderer, float scale);

	std::vector<Rectangle> checkTileCollisions(const Rectangle &other);
	std::vector<Enemy*> checkEnemyCollisions(const Rectangle &other);

	inline glb::Vec2f getPlayerSpawnPoint() { return _spawnPoint; }

private:
	void loadMap(std::string mapName, SDL_Renderer &renderer, float scale);

	std::string _mapName;
	glb::Vec2f _spawnPoint;
	glb::Vec2i _size;

	glb::Vec2i _tileSize;

	std::vector<Tile> _tileList;
	std::vector<Tileset> _tilesets;
	std::vector<Rectangle> _collRects;

	std::vector<Enemy*> _enemies;
	
};



struct Tileset
{
	SDL_Texture* Texture;
	int FirstGid;

	Tileset()
	{
		FirstGid = -1;
	}

	Tileset(SDL_Texture* texture, int firstGid)
	{
		Texture = texture;
		FirstGid = firstGid;
	}
};