#include "../headers/Player.h"


Player::~Player()
{
	SDL_DestroySurface(mp_sprite);
}

void Player::update()
{
	//handlePlayerInput(_event);

}


void Player::handlePlayerInput(SDL_Event _event)
{
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


