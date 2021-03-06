///////////////////////////////////////////////////////////////////////////////////////////////////////
//  Author  : Zac King  ///////////////////////////////////////////////////////////////////////////////
//  Origin  : Marco Salamone  /////////////////////////////////////////////////////////////////////////
//  Date    : 24/10/2014  /////////////////////////////////////////////////////////////////////////////
//  Purpose : Declaration Header  /////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Aie.h"
#include <time.h>
#include <cmath>

// Global Variables  //////////////////////////////////////////////////////////////////////////////////
const int g_w = 790;		  // Global Screen Width  /////////////////////////////////////////////////
const int g_h = 680;		  // Global Screen Height  ////////////////////////////////////////////////
const int g_maxSprites  = 64; // Global Sprite max  ///////////////////////////////////////////////////
const int g_maxBullets  = 64; // Global Bullet max  ///////////////////////////////////////////////////
const int g_maxEnemies  = 64; // Global Enemy Max  ////////////////////////////////////////////////////
const int g_maxEntities = 96; // Global max entities on screen at one time  ///////////////////////////
// Enum Variables  ////////////////////////////////////////////////////////////////////////////////////
enum eSpriteFlag { eNone, ePlayer, eShot, eEnemy, eSize, eSpawner, eHealthBar, eShrine, eBackground, eBackGround_MM, eBackGround_B };
enum e_direction { eUp, eDown, eLeft, eRight };
enum e_GState	 { eMainMenu, eGame, eControl, eScore, ePause, eLost, eControlChange, eExit };
// Forward Declarations  //////////////////////////////////////////////////////////////////////////////
class Assets;  ////////////////////////////////////////////////////////////////////////////////////////
class GameState;  /////////////////////////////////////////////////////////////////////////////////////
class Player;  ////////////////////////////////////////////////////////////////////////////////////////
class Shrine;  ////////////////////////////////////////////////////////////////////////////////////////
class Enemy;  /////////////////////////////////////////////////////////////////////////////////////////
class Bullet;  ////////////////////////////////////////////////////////////////////////////////////////
class EnemySpawn;  ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

class Entity
{
protected:
	float m_x, m_y;		// Position
	float m_speed;		// Speed
	int m_h, m_w;		// Dimensions
	int m_w2;			// Half width
	int m_health;		// Health
	bool m_alive;		// Object state
	unsigned m_sprite;	// Sprite
	GameState *e_gs;	// Current GameState
	enum Type			// Sprite Flag
	{ e_Bullet, e_Player, e_Enemy, e_Shrine};

public:
		//Entity(GameState *a_gs) : e_gs(a_gs) {}
	virtual void Update(float a_dt)			{}
	virtual void Draw()						{}
	virtual void onHit()					{}
	virtual void onCollide(const Entity *e)	{}
	// Radious collison
	bool Collides(const Entity *e)			{ return distanceBetween(e) < ((m_w2) + (e->m_w2)); }
	// A^2 + B^2 = C^2
	int distanceBetween(const Entity *e)	{ return sqrt( ( (m_x - e->m_x)*(m_x - e->m_x) ) + ( (m_y - e->m_y)*(m_y - e->m_y) ) ); }
	// Entity Getters
	int getX()			{ return m_x;	  }
	int getY()			{ return m_y;	  }
	int getHealth()	    { return m_health;}
	int getHalfWidth()	{ return m_w2;	  }
};
