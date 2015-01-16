///////////////////////////////////////////////////////////////////////////////////////////////////////
//  Author  : Zac King  ///////////////////////////////////////////////////////////////////////////////
//  Origin  : Zac King  ///////////////////////////////////////////////////////////////////////////////
//  Date    : 24/10/2014  /////////////////////////////////////////////////////////////////////////////
//  Purpose : Enemy objects ///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Assets.h"
#include "GameState.h"
#include <random>
#include <ctime>

// Constructor  ///////////////////////////////////////////////////////////////////////////////////////
Enemy::Enemy(unsigned a_sprite, float a_x, float a_y, int a_w, int a_h, float a_speed, float a_fDelay, Player *a_p)
{
	m_x = a_x;
	m_y = a_y;
	m_w = a_w;
	m_h = a_h;
	m_speed = a_speed;
	m_sprite = a_sprite;
	m_target = a_p;
	m_w2 = m_w / 2;
	m_alive = true;
}
// Move Towards the player  ///////////////////////////////////////////////////////////////////////////
void Enemy::Pursue(float a_dt)
{
	// Move towrads Target's X, Y coordinates
	if ((m_target->getX()) - m_x < m_w2) m_x -= m_speed * a_dt;
	if (m_x - (m_target->getX()) < m_w2) m_x += m_speed * a_dt;

	if ((m_target->getY()) - m_y < m_w2) m_y -= m_speed * a_dt;
	if (m_y - (m_target->getY()) < m_w2) m_y += m_speed * a_dt;
}
// Update Enemy values  ///////////////////////////////////////////////////////////////////////////////
void Enemy::Update(float a_dt)
{
	// Sensing range
	if (distanceBetween(m_target) < 175)
		Pursue(a_dt);
	// Move towrads Shrine's X, Y coordinates
	else
	{
		if ((g_w / 2) - m_x < m_w2) m_x -= m_speed * a_dt;
		if (m_x - (g_w / 2) < m_w2) m_x += m_speed * a_dt;

		if ((g_h / 2) - m_y < m_w2) m_y -= m_speed * a_dt;
		if (m_y - (g_h / 2) < m_w2) m_y += m_speed * a_dt;
	}
}
// Draw Enemy  ////////////////////////////////////////////////////////////////////////////////////////
void Enemy::Draw()
{
	MoveSprite(m_sprite, m_x, m_y);
	DrawSprite(m_sprite);
}
// Actions for a Collison  ////////////////////////////////////////////////////////////////////////////
void Enemy::onCollide()
{
	m_alive = false;
	m_target->setScore(15);
}
// Check if Enemy is still alive  /////////////////////////////////////////////////////////////////////
bool Enemy::IsActive()
{
	return m_alive;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// Enemy Spawner Constructor  /////////////////////////////////////////////////////////////////////////
EnemySpawn :: EnemySpawn(GameState *a_gs, unsigned a_sprite, float a_x, float a_y, int a_w, int a_h, float a_speed, float a_fDelay, e_direction a_dir)
{
	e_gs = a_gs;
	m_x = a_x;
	m_y = a_y;
	m_w = a_w;
	m_h = a_h;
	m_emitDelay = a_fDelay;
	m_speed = a_speed;
	m_sprite = a_sprite;
	m_scroll = a_dir;
}
// Enemy Spawner Update  //////////////////////////////////////////////////////////////////////////////
void EnemySpawn :: Update(float a_dt)
{
	// Scroll controls / Boundry checks
	switch (m_scroll)
	{
		case eLeft:
		{
			m_x -= m_speed * a_dt;
			if (m_x < (32))     m_speed *= -1;
			if (m_x >(g_w - 32)) m_speed *= -1;
		} break;
		case eRight:
		{
			m_x += m_speed * a_dt;
			if (m_x < (32))      m_speed *= -1;
			if (m_x >(g_w - 32)) m_speed *= -1;
		} break;
		case eUp:
		{
			m_y -= m_speed * a_dt;
			if (m_y < (32))     m_speed *= -1;
			if (m_y >(g_h - 90)) m_speed *= -1;
		} break;
		case eDown:
		{
			m_y += m_speed * a_dt;
			if (m_y < (32))     m_speed *= -1;
			if (m_y >(g_h - 90)) m_speed *= -1;
		} break;
	}
	// Spawner Delay
	m_timer += a_dt / (rand() % 2 + 1);
	if (m_timer > m_emitDelay)
	{ m_timer = -(rand() % 5 + 1); e_gs->SpawnEnemy(m_x, m_y); }
}
// Enemy Spawner Draw  ////////////////////////////////////////////////////////////////////////////////
void EnemySpawn::Draw()
{
	MoveSprite(m_sprite, m_x, m_y);
	DrawSprite(m_sprite);
}