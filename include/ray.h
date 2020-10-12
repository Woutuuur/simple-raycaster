#include <SDL2/SDL.h>

class Ray
{
	public:
		Ray();
		Ray(SDL_Renderer *ren, double x, double y, double angle);
		double cast(const int wallX, const int wallY, const double wallW, const double wallH);
		void render(const double destX, const double destY);
		double getX() {return x;}
		double getY() {return y;}
	private:
		double x, y;
		double angle;
		SDL_Renderer *renderer;
};