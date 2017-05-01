#include "Errors.h"

#include <cstdlib>
#include <iostream>
#include <SDL\SDL.h>

//Ivykus klaidai programa isjungiama ir konsoleje parasoma kas ivyko
void fatalError(std::string errString)
{
	std::cout << errString << std::endl
		<< "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(8);
}