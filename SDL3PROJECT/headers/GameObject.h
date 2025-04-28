#pragma once
#include <cstdio>
#include <SDL3/SDL.h>
#include "Collider.h"
#include "ControllerComponent.h"


class GameObject 
{
public:
	GameObject()
	{
		m_playerCanMove = true;
		m_playerStep = 120;
		m_prevX = 0;
		m_prevY = 0;
		m_rect = { 0,0,120,120 };
		mp_sprite = nullptr;
		p_controller = nullptr;
	};
	~GameObject();
	void update(SDL_Event _event);

	void attachController(ControllerComponent* controller) { p_controller = controller; };
	void attachSprite(SDL_Surface* p_sprite) { mp_sprite = p_sprite; };

	ControllerComponent* getController() { if (p_controller != nullptr) { return p_controller; } return nullptr; };

	SDL_Rect& getRect() { return m_rect; };
	void setRectPrev();

	bool checkCollision(SDL_Rect other);

private:
	SDL_Rect m_rect;
	int m_playerStep;
	bool m_playerCanMove;

	int m_prevX = 0;
	int m_prevY = 0;

	//does not own these
	SDL_Surface* mp_sprite;
	ControllerComponent* p_controller;


};