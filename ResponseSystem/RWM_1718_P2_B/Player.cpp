#include "Player.h"

Player::Player(SDL_Renderer* renderer)
{
	m_renderer = renderer;
	Init();
}

void Player::Init()
{
	m_rect->x = 100;
	m_rect->y = 100;
	m_rect->w = 50;
	m_rect->h = 50;

	m_centrePoint.x = m_rect->w * 0.5f;
	m_centrePoint.y = m_rect->h * 0.5f;

	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(m_rect->x, m_rect->y);

	//m_shape->SetAsBox(50.0f, 50.0f, b2Vec2(25,25),0);
}