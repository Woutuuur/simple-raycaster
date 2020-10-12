#include "ray.h"
#include "options.h"

Ray::Ray(SDL_Renderer *ren, double x, double y, double angle)
{
	renderer = ren;
	this->x = x;
	this->y = y;
	this->angle = angle;
}

void Ray::render(const double destX, const double destY)
{
	SDL_RenderDrawLine(renderer, x, y, destX, destY);
}

double Ray::cast(const int wallX, const int wallY, const double wallW, const double wallH)
{
	bool hitWall = false;
	double dist = 0.0f;
	double x2 = x;
	double y2 = y;
	while (!hitWall)
	{
		dist += STEP_SIZE;
		x2 = x + dist * std::cos(DEG2RAD * angle);
		y2 = y + dist * -std::sin(DEG2RAD * angle);
		if (x2 > wallX * wallW && x2 < wallX * wallW + wallW && y2 > wallY * wallH && y2 < wallY * wallH + wallH)
			return dist;
		if (x2 > SCREEN_WIDTH / 3 || y2 > SCREEN_HEIGHT || x2 < 0 || y2 < 0)
			return dist;
	}
	return 0;
}