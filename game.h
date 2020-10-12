#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "player.h"

class Game
{
public:
	Game();
	Game(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
	~Game();
	void readMap(const std::string fileName);
	void update(double dT);
	void render();	
	bool running();
	void handleEvents(const double dT);
	void quit();
	void renderGrid();
	void renderRays();
private:
	bool isRunning;
	SDL_Window *window;
	SDL_Renderer *renderer;
	std::pair<int, int> playerPos;
	std::vector<std::vector<char>> map;
	uint32_t startTime;
	Player *player;
	void draw3D(const double dist, const double i);
	int r = 255, g = 0, b = 0;
};

#endif