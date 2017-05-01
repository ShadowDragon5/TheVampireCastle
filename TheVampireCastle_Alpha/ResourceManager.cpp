#include "ResourceManager.h"

std::map<std::string, SDL_Surface*> ResourceManager::_spriteSheets;

//Loads image
SDL_Surface* ResourceManager::loadImage(const std::string &filePath)
{
	if (_spriteSheets.count(filePath) == 0)
	{
		_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return _spriteSheets[filePath];
}