#pragma once
#include "Box2D\Box2D.h"
#include "SDL.h"

class Player
{
public:
	Player();
	void Init();
private:
	SDL_Rect m_rect;
	SDL_Point m_centrePoint;

	b2Body* m_body;
	b2BodyDef m_bodyDef;

	SDL_Renderer* m_renderer;
	SDL_Surface* m_surface;
	SDL_Texture* m_texture;

	b2Vec2 m_position;
	b2Vec2 m_velocity;

};