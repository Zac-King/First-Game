///////////////////////////////////////////////////////////////////////////////////////////////////////
//  Author  : Zac King  ///////////////////////////////////////////////////////////////////////////////
//  Origin  : Marco Salamone  /////////////////////////////////////////////////////////////////////////
//  Date    : 24/10/2014  /////////////////////////////////////////////////////////////////////////////
//  Purpose : Manages Bullet objects  /////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Bullet.h"
#include "Player.h"
#include "GameState.h"

// Bullet Construcctor  ///////////////////////////////////////////////////////////////////////////////
Bullet::Bullet(GameState *a_gs, unsigned a_sprite, float a_x, float a_y, int a_w, int a_h, float a_speed, int a_direction)
{
	e_gs = a_gs;
	m_speed = a_speed;
	m_x = a_x;
	m_y = a_y;
	m_w = a_w;
	m_h = a_h;
	m_sprite = a_sprite;
	m_direction = a_direction;
	m_w2 = m_w / 2;
	m_alive = true;
}
// Bullet Update (check collison/make nessary changes)  ///////////////////////////////////////////////
void Bullet::Update(float a_dt)
{
	// Checking Player's firing direction
	switch (m_direction)
	{
	case eUp   : m_y += m_speed * a_dt; break;
	case eDown : m_y -= m_speed * a_dt; break;
	case eLeft : m_x -= m_speed * a_dt; break;
	case eRight: m_x += m_speed * a_dt; break;
	}
	// Checking collison   [Enemies]
	for (int j = 0; j < g_maxEnemies; ++j)
	{
		Enemy *t = e_gs->GetEnemy(j);

		if (t && t->IsActive())
		{
			if (Collides(t))
			{
				this->onCollide();
				t->onCollide();
			}
		}
	}
}
// Draw Bullet sprite  ////////////////////////////////////////////////////////////////////////////////
void Bullet::Draw()
{
	// ... isn't obvious
	MoveSprite(m_sprite, m_x, m_y);
	DrawSprite(m_sprite);
}
// Check to see if bullet is alive  ///////////////////////////////////////////////////////////////////
bool Bullet::IsActive()
{

	if (m_alive)
	return (m_x > 0) && (m_x < g_w) && (m_y < g_h - 85) && (m_y > 0);

	else
		return false;
}
// Check collison  ////////////////////////////////////////////////////////////////////////////////////
void Bullet::onCollide()
{
	this->m_alive = false;
}