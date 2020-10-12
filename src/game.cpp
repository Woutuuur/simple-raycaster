#include "game.h"
#include "options.h"

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	startTime = SDL_GetTicks();
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw std::runtime_error("Could not initialize SDL.");
	window = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
	if (!window)
		throw std::runtime_error("Could not initialize window.");
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
		throw std::runtime_error("Could not initialize renderer.");
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	isRunning = true;
}

void Game::readMap(const std::string fileName)
{
	std::fstream FS;
	FS.open(fileName);
	if (!FS.is_open())
		throw std::runtime_error("Could not open file " + fileName);
	std::vector<char> row;
	int x, y;
	FS >> x >> y;
	player = new Player(renderer, x, y);
	FS >> x >> y;
	char curr;
	for (int i = 0; i < y; i++)
	{
		std::vector<char> row;
		for (int j = 0; j < x; j++)
		{
			FS >> curr;
			row.push_back(curr);
		}
		map.push_back(row);
	}
	FS.close();
}

bool Game::running()
{
	return isRunning;
}

void Game::handleEvents(const double dT)
{
	SDL_Event event;
	
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	player->handleKeyPresses(keystate, dT);	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				isRunning = false;
				break;
			default:
				break;
		}
	}

}

double nmap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Game::draw3D(const double dist, const double c)
{
	SDL_Rect rect;
	rect.x = SCREEN_WIDTH / 3 + (SCREEN_WIDTH * 2 / 3) / RAYS * c;
	rect.w = SCREEN_WIDTH * 2 / 3 / RAYS;
	rect.h = nmap(dist, 0, SCREEN_HEIGHT, SCREEN_HEIGHT, 0);
	rect.y = (SCREEN_HEIGHT - rect.h)/2;
	SDL_SetRenderDrawColor(renderer, nmap(dist, 0, SCREEN_HEIGHT, 255, 0), nmap(dist, 0, SCREEN_HEIGHT, 255, 0), nmap(dist, 0, SCREEN_HEIGHT, 255, 0), 255);
	SDL_RenderFillRect(renderer, &rect);
}

void Game::renderRays()
{
	const int h = SCREEN_HEIGHT / map.size();
	const int w = SCREEN_WIDTH / 3 / map.at(0).size();
	for (int c = 0; c < RAYS; c++)
	{
		double fovOffset = nmap(c, 0, RAYS, -FOV/2, FOV/2);
		double minDist = 10000;
		double dist = 0;
		Ray ray = Ray(renderer, player->getX(), player->getY(), player->getAngle() + fovOffset);
		for (int i = 0; i < map.size(); i++)
		{

			for (int j = 0; j < map.at(i).size(); j++)
			{
				if (map.at(i).at(j) == WALL)
					dist = ray.cast(j, i, w, h);
				if (dist < minDist)
					minDist = dist;
			}
		}
		double destX = player->getX() + minDist *  std::cos(DEG2RAD * (player->getAngle() + fovOffset));
		double destY = player->getY() + minDist * -std::sin(DEG2RAD * (player->getAngle() + fovOffset));
		ray.render(destX, destY);
		draw3D(minDist, c);
	}
}

void Game::renderGrid()
{
	const int h = SCREEN_HEIGHT / map.size();
	const int w = SCREEN_WIDTH / 3 / map.at(0).size();
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map.at(i).size(); j++)
		{
			SDL_Rect rect;
			rect.x = j * w;
			rect.y = i * h;
			rect.w = w;
			rect.h = h;
			if (map.at(i).at(j) == WALL)
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			else
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	renderGrid();
	renderRays();
	player->render();
	SDL_RenderPresent(renderer);
}

void Game::update(double dT)
{
	player->move(dT);
}

void Game::quit()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
