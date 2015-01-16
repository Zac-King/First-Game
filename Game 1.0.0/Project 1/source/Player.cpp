///////////////////////////////////////////////////////////////////////////////////////////////////////
//  Author  : Zac King  ///////////////////////////////////////////////////////////////////////////////
//  Origin  : Zac King  ///////////////////////////////////////////////////////////////////////////////
//  Date    : 24/10/2014  /////////////////////////////////////////////////////////////////////////////
//  Purpose : Player objects  /////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Player.h"
#include "GameState.h"
#include "Assets.h"

// Player Constructor  ////////////////////////////////////////////////////////////////////////////////
Player::Player(GameState *a_gs, unsigned a_sprite, float a_x, float a_y, int a_w, int a_h, float a_speed, float a_fDelay)
{
	e_gs		= a_gs;
	m_x			= a_x;
	m_y			= a_y;
	m_w			= a_w;
	m_h			= a_h;
	m_speed		= a_speed;
	m_sprite	= a_sprite;
	m_fSpeed	= 300;		 
	m_fDelay	= a_fDelay;
	m_fTimer	= 0;       
	m_lastHit	= 0;
	m_w2		= m_w / 2; 
	m_health	= 100;
	m_score		= 0;
	// only use padding if e_gs isn't null
	if (e_gs) m_pad = e_gs->GetPadding(); 
	else m_pad = 0; //otherwise we have no padding, use screen dimensions
}											
// Fire a Bullet  /////////////////////////////////////////////////////////////////////////////////////
void Player::Fire()
{
	// Fire delay
	if (m_fTimer > m_fDelay)
	{
		m_fTimer = 0;
		e_gs->SpawnBullet(m_x, m_y, m_fSpeed, m_facing);
	}
}
// Take damage from a collison  ///////////////////////////////////////////////////////////////////////
void Player::takeDamage()
{
	// Space out the time between each hit
	if (m_lastHit > 0.45f)
	{
		m_lastHit = 0;
		m_health -= 5;
	}
}
// Actions for a collison  ////////////////////////////////////////////////////////////////////////////
void Player::onCollide()
{
	// In retrospect perhaps i didn't need make a sperate function for the damage, but YOLO right?
	if (m_health > 0)
		takeDamage();
}
// Update Player values  //////////////////////////////////////////////////////////////////////////////
void Player::Update(float a_dt)
{
	m_lastHit += a_dt;
	m_fTimer += a_dt; 
	// Control Input
	if (ControlManager::isKeyDown(e_left))	{ m_x -= m_speed * a_dt; }
	if (ControlManager::isKeyDown(e_right)) { m_x += m_speed * a_dt; }
	if (ControlManager::isKeyDown(e_down))	{ m_y -= m_speed * a_dt; }
	if (ControlManager::isKeyDown(e_up))	{ m_y += m_speed * a_dt; }
	if (ControlManager::isKeyDown(e_fire))	Fire();
			//if (IsKeyDown('A')) { m_x -= m_speed * a_dt; }	// Controls.IsKeyDown(eLeft))
			//if (IsKeyDown('D')) { m_x += m_speed * a_dt; }  // 
			//if (IsKeyDown('S')) { m_y -= m_speed * a_dt; }
			//if (IsKeyDown('W')) { m_y += m_speed * a_dt; }
			//if (IsKeyDown(' ')) Fire();
	// Lock firing direction
	if (!ControlManager::isKeyDown(e_lock))
	{
		if (ControlManager::isKeyDown(e_left))  { m_facing = eLeft; }
		if (ControlManager::isKeyDown(e_right)) { m_facing = eRight; }
		if (ControlManager::isKeyDown(e_down))  { m_facing = eDown; }
		if (ControlManager::isKeyDown(e_up))	{ m_facing = eUp; }
	}
	// Boundry check
	if (m_x <   0 + (m_pad + m_w2)) m_x =   0 + (m_pad + m_w2);
	if (m_x > g_w - (m_pad + m_w2)) m_x = g_w - (m_pad + m_w2);
	if (m_y <   0 + (m_pad + m_h)) m_y =   0 + (m_pad + m_h);
	if (m_y > g_h - ((m_pad + m_h)+48)) m_y = g_h - ((m_pad + m_h)+48);
	// Checking Enemy Collison
	for (int j = 0; j < g_maxEnemies; j++)
	{
		// temp created to use in loop
		Enemy *t = e_gs->GetEnemy(j); 
		if (t && t->IsActive())
		{
			if (Collides(t))
				onCollide();
		}
	}
}
// Draw Player  ///////////////////////////////////////////////////////////////////////////////////////
void Player::Draw()
{
	MoveSprite(m_sprite, m_x, m_y);
	DrawSprite(m_sprite);
}
// Check if Player is alive  //////////////////////////////////////////////////////////////////////////
bool Player::Dead()
{
	// "Are you still There?" - Portal Turret
	if (m_health > 0) return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// Shrine Constructor  ////////////////////////////////////////////////////////////////////////////////
Shrine::Shrine(GameState *a_gs, unsigned a_sprite, float a_x, float a_y, int a_w, int a_h)
{
	e_gs = a_gs;
	m_x = a_x;
	m_y = a_y;
	m_w = a_w;
	m_h = a_h;
	m_sprite = a_sprite;
	m_lastHit = 0;
	m_w2 = m_w / 2;
	m_health = 150;
}
// Update Shrine values  //////////////////////////////////////////////////////////////////////////////
void Shrine::Update(float a_dt)
{
	m_lastHit += a_dt;

	for (int j = 0; j < g_maxEnemies; j++)
	{
		Enemy *t = e_gs->GetEnemy(j);

		if (t && t->IsActive())
		{
			if (Collides(t))
				onCollide();
		}
	}
}
// Draw Shrine  *Place holder  ////////////////////////////////////////////////////////////////////////
void Shrine::Draw()
{
	MoveSprite(m_sprite, m_x, m_y);
	DrawSprite(m_sprite);
}
// Actions for a collison /////////////////////////////////////////////////////////////////////////////
void Shrine::onCollide()
{
	if (m_health > 0)
	{
		if (m_lastHit > 0.75f)
		{
			m_lastHit = 0;
			m_health -= 5;
		}
	}
}