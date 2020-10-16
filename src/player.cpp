#include "player.h"
#include "options.h"
#include <SDL2/SDL.h>
#include <iostream>

#define PLAYER_WIDTH 5
#define PLAYER_HEIGHT 5
#define MAX_VELOCITY 0.1


void Player::move(double deltaTime)
{
	if (velocity < -MAX_VELOCITY) velocity = -MAX_VELOCITY;
	if (velocity > MAX_VELOCITY) velocity = MAX_VELOCITY;
	x += velocity * deltaTime * std::cos(PI / 180 * angle);
	y += velocity * deltaTime * -std::sin(PI / 180 * angle);
	if (x > SCREEN_WIDTH / 3 - PLAYER_WIDTH) x = SCREEN_WIDTH / 3 - PLAYER_WIDTH;
	if (y > SCREEN_HEIGHT - PLAYER_HEIGHT) y = SCREEN_HEIGHT - PLAYER_HEIGHT;
	if (x < 0) x = 0;
	if (y < 0) y = 0;
}


Player::Player(SDL_Renderer *ren, const float x, const float y)
{
	renderer = ren;
	this->x = x;
	this->y = y;
	velocity = 0;
	angle = 0;
}

Player::~Player()
{
	SDL_DestroyRenderer(renderer);
}

void Player::handleKeyPresses(const Uint8*& keystate, const double deltaTime)
{
	if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W])
		if (velocity < MAX_VELOCITY) velocity += 0.01;
	if (keystate[SDL_SCANCODE_DOWN]| keystate[SDL_SCANCODE_S])
		if (velocity > -MAX_VELOCITY) velocity -= 0.01;
	if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D])
	{
		angle -= 0.1 * deltaTime;
		if (angle < 0) angle += 360;
	}
	if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A])
	{
		angle += 0.1 * deltaTime;
		if (angle > 360) angle -= 360;
	}
	if (!(keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_W]))
	{
		if (velocity > 0) velocity = 0;
		if (velocity < 0) velocity = 0;
	}
}

void Player::render()
{
	SDL_Rect playerRect;
	playerRect.x = x;
	playerRect.y = y;
	playerRect.w = PLAYER_WIDTH;
	playerRect.h = PLAYER_HEIGHT;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &playerRect);
	SDL_RenderDrawLine(renderer, x + PLAYER_WIDTH/2, y + PLAYER_HEIGHT/2, x + PLAYER_WIDTH/2 + 20 * std::cos(DEG2RAD * angle), y + PLAYER_HEIGHT/2 + 20 * -std::sin(DEG2RAD * angle));
}
