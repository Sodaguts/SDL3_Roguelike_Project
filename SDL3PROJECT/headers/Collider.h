#include <SDL3/SDL.h>

//use to check if spaces are occupied or out of range per actor in scene
//only does box collisions
class Collider 
{
public:
	Collider() { m_rect = {0,0,0,0}; }; 
	Collider(int posX, int posY, int length, int width);

	bool checkCollision(SDL_Rect other); 

	void setColliderSize(int x, int y) { m_rect.x = x; m_rect.y = y; };
	void setColliderPos(int w, int h) { m_rect.w = w; m_rect.h = h; };

	SDL_Rect getRect() { return m_rect; };
private:
	SDL_Rect m_rect;
};