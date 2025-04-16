#pragma once
#include <SDL3/SDL.h>
#include <cstdio>


class ControllerComponent 
{
public:
	ControllerComponent();
	~ControllerComponent() {};

	int getX() { return m_posX; };
	int getY() { return m_posY; };

	void update(SDL_Event _event);
	void setStepAmount(int amount) { m_stepAmount = amount; };
	void setPosition(int x, int y) { m_posX = x; m_posY = y; };

private:
	int m_posX;
	int m_posY;
	int m_stepAmount;
	bool m_canMove;

	void updateCanMove() { m_canMove = !m_canMove; };
};