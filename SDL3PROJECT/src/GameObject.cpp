#include "../headers/GameObject.h"


GameObject::~GameObject()
{
	SDL_DestroySurface(mp_sprite);
}

void GameObject::update()
{
	//handlePlayerInput(_event);
}


void GameObject::handlePlayerInput(SDL_Event _event)
{
	m_prevX = m_posX;
	m_prevY = m_posY;
	switch (_event.type)
	{
	case SDL_EVENT_KEY_DOWN:
		if (m_playerCanMove)
		{
			if (_event.key.key == SDLK_LEFT)
			{
				m_posX -= m_playerStep;
				m_rect = { m_posX, m_posY, 120,120 };
				m_playerCanMove = false;

			}
			if (_event.key.key == SDLK_RIGHT)
			{
				m_posX += m_playerStep;
				m_rect = { m_posX, m_posY, 120,120 };
				m_playerCanMove = false;
			}
			if (_event.key.key == SDLK_UP)
			{
				m_posY -= m_playerStep;
				m_rect = { m_posX, m_posY, 120,120 };
				m_playerCanMove = false;
			}
			if (_event.key.key == SDLK_DOWN)
			{
				m_posY += m_playerStep;
				m_rect = { m_posX, m_posY, 120,120 };
				m_playerCanMove = false;
			}
		}
		break;
	case SDL_EVENT_KEY_UP:
		if (_event.key.key == SDLK_LEFT)
		{
			m_playerCanMove = true;
		}
		if (_event.key.key == SDLK_RIGHT)
		{
			m_playerCanMove = true;
		}
		if (_event.key.key == SDLK_UP)
		{
			m_playerCanMove = true;
		}
		if (_event.key.key == SDLK_DOWN)
		{
			m_playerCanMove = true;
		}
		break;
	}
}

void GameObject::setRectPrev()
{
	m_posX = m_prevX;
	m_posY = m_prevY;
	m_rect.x = m_prevX;
	m_rect.y = m_prevY;
}


