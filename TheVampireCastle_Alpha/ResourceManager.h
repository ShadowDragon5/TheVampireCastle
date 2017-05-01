#pragma once
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <string>
#include <map>

class ResourceManager
{
public:
	static SDL_Surface* loadImage(const std::string &filePath);

private:
	static std::map<std::string, SDL_Surface*> _spriteSheets;
};

