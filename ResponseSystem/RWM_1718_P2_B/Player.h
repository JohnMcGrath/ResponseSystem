#pragma once
#include "Box2D\Box2D.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Player
{
public:
	Player(SDL_Renderer* renderer);

	void Init();

	SDL_Texture* GetTexture() { return m_texture; }
	SDL_Point GetCentrePoint() { return m_centrePoint; }
	SDL_Rect* GetRect() { return m_rect; }
	b2BodyDef GetBodyDef() { return m_bodyDef; }
	b2Body* GetBody() { return m_body; }
	b2PolygonShape* GetShape() { return m_shape; }

	void SetBody(b2Body* newBody) { m_body = newBody; }


private:
	SDL_Rect* m_rect = new SDL_Rect();
	SDL_Point m_centrePoint;

	b2Body* m_body;
	b2PolygonShape* m_shape;
	b2BodyDef m_bodyDef;

	SDL_Renderer* m_renderer;
	SDL_Surface* m_surface;
	SDL_Texture* m_texture;

	b2Vec2 m_position;
	b2Vec2 m_velocity;
};