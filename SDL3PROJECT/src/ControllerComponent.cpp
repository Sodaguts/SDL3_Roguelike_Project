#include "ControllerComponent.h"

ControllerComponent::ControllerComponent()
{
	m_posX = 0;
	m_posY = 0;
	m_stepAmount = 120;
	m_canMove = true;
}

void ControllerComponent::update(SDL_Event _event)
{
	switch (_event.type)
	{
		case SDL_EVENT_KEY_DOWN:
			if (_event.key.type == SDLK_LEFT) 
			{
				m_posX -= m_stepAmount;
				updateCanMove();
			}
			if (_event.key.type == SDLK_RIGHT) 
			{
				m_posX += m_stepAmount;
				updateCanMove();
			}
			if (_event.key.type == SDLK_UP) 
			{
				m_posY -= m_stepAmount;
				updateCanMove();
			}
			if (_event.key.type == SDLK_DOWN) 
			{
				m_posY += m_stepAmount;
				updateCanMove();
			}
		case SDL_EVENT_KEY_UP:
			if (_event.key.type == SDLK_LEFT)
			{
				updateCanMove();
			}
			if (_event.key.type == SDLK_RIGHT)
			{
				updateCanMove();
			}
			if (_event.key.type == SDLK_UP)
			{
				updateCanMove();
			}
			if (_event.key.type == SDLK_DOWN)
			{
				updateCanMove();
			}
	}
}

