#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <stdexcept>
#include "game.h"
#include "options.h"

int main(int argc, const char *argv[])
{
	Uint32 newTime, currentTime;
	Uint32 frameTime = 0.0;
	try 
	{
		Game* game = new Game("raycaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
		if (argc < 2)
			throw std::runtime_error("No filename given.");
		std::string fileName = argv[1];
		game->readMap(fileName);
		currentTime = SDL_GetTicks();
		while (game->running())
		{
			game->handleEvents(frameTime);
			game->update(frameTime);

			newTime = SDL_GetTicks();
			frameTime = newTime - currentTime;
			currentTime = newTime;
			game->render();
		}
		game->quit();
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	
	return 0;
}
