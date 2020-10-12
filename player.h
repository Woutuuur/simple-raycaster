#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>
#include <vector>
#include <SDL2/SDL.h>
#include "ray.h"

class Player
{
	public:
		Player();
		Player(SDL_Renderer *ren, const float x, const float y);
		~Player();
		void move(double deltaTime);
		double getX() {return x;}
		double getY() {return y;}
		double getAngle() {return angle;}
		void render();
		void handleKeyPresses(const Uint8*& keystate, const double deltaTime);
	private:
		double x, y;
		double angle;
		SDL_Renderer *renderer;
		float velocity;
};

#endif