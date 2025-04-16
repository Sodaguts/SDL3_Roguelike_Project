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
				if (m_canMove) 
				{
					if (_event.key.key == SDLK_LEFT)
					{
						m_posX -= m_stepAmount;
						m_canMove = false;
					}
					if (_event.key.key == SDLK_RIGHT)
					{
						m_posX += m_stepAmount;
						m_canMove = false;
					}
					if (_event.key.key == SDLK_UP)
					{
						m_posY -= m_stepAmount;
						m_canMove = false;
					}
					if (_event.key.key == SDLK_DOWN)
					{
						m_posY += m_stepAmount;
						m_canMove = false;
					}
				}
				break;
			case SDL_EVENT_KEY_UP:
				if (_event.key.key == SDLK_LEFT)
				{
					m_canMove = true;
				}	
				if (_event.key.key == SDLK_RIGHT)
				{
					m_canMove = true;
				}
				if (_event.key.key == SDLK_UP)
				{
					m_canMove = true;
				}
				if (_event.key.key == SDLK_DOWN)
				{
					m_canMove = true;
				}
				break;
	}
}

