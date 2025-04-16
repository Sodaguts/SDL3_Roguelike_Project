#include "../headers/GameObject.h"


GameObject::~GameObject()
{
	SDL_DestroySurface(mp_sprite);
}

void GameObject::update(SDL_Event _event)
{
	if (p_controller != nullptr) 
	{
		m_prevX = p_controller->getX();
		m_prevY = p_controller->getY();
		p_controller->update(_event);
		m_rect = {p_controller->getX(), p_controller->getY(), 120,120};
	}
}

void GameObject::setRectPrev()
{
	if (p_controller != nullptr) 
	{
		p_controller->setPosition(m_prevX, m_prevY);
	}
	m_rect.x = m_prevX;
	m_rect.y = m_prevY;
}

bool GameObject::checkCollision(SDL_Rect other)
{
	int leftA = m_rect.x;
	int rightA = m_rect.x + m_rect.w;
	int topA = m_rect.y;
	int botA = m_rect.y + m_rect.h;

	int leftB = other.x;
	int rightB = other.x + other.w;
	int topB = other.y;
	int botB = other.y + other.h;

	if (botA <= topB)
	{
		return false;
	}

	if (topA >= botB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}
	return true;
}


