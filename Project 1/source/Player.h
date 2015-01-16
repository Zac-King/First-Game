///////////////////////////////////////////////////////////////////////////////////////////////////////
//  Author  : Zac King  ///////////////////////////////////////////////////////////////////////////////
//  Origin  : Zac King  ///////////////////////////////////////////////////////////////////////////////
//  Date    : 24/10/2014  /////////////////////////////////////////////////////////////////////////////
//  Purpose : Player Header  //////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Decl.h"

class Player : public Entity
{
	float m_speed;				// Movement Speed
	float m_fSpeed;				// Fire Speed 
	double m_score;				// Player's Score
	float m_fDelay, m_fTimer;	// Firing controls (delay between each shot fired, ) 
	float m_lastHit;			// Time from last hit
	int m_pad;					// For boundary collision.
	e_direction m_facing = eUp;	// Firing direction. 
	GameState *e_gs;			// Pointer to GameState

public:
	Player(GameState *a_gs, unsigned a_sprite, float a_x, float a_y, int a_w, int a_h, float a_speed, float a_fDelay);
	
	void Update(float a_dt);
	void Draw();
	void takeDamage();
	bool Dead();
	void Fire();
	void onCollide();
	double getScore()		{ return m_score; }
	void setScore(int a)	{ m_score += a; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////
class Shrine : public Entity
{
	float m_lastHit;
	public:
		Shrine(GameState *a_gs, unsigned a_sprite, float a_x, float a_y, int a_w, int a_h);

		void Update(float a_dt);
		void Draw();
		void onCollide();
		void takeDamage();
};
