///////////////////////////////////////////////////////////////////////////////////////////////////////
//  Author  : Zac King  ///////////////////////////////////////////////////////////////////////////////
//  Origin  : Marco Salamone  /////////////////////////////////////////////////////////////////////////
//  Date    : 24/10/2014  /////////////////////////////////////////////////////////////////////////////
//  Purpose : Gamestate Header  ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Decl.h"
#include "Enemy.h"
#include "Player.h"
#include <vector>
#include <queue>

class GameState
{
	unsigned int backgroundSprite =		   CreateSprite("./images/BackGround_Sprite.png", 790, 680, 1);
	unsigned int healthBar_sprite =		   CreateSprite("./images/HealthBar_TestSprite.png", 8, 32, 1);
	unsigned int shrine_healthBar_sprite = CreateSprite("./images/Shrine_TestSprite.png", 8, 32, 1);
	Player	   *m_player;
	Shrine	   *m_shrine;
	Enemy	   *m_enemy[g_maxEnemies];
	//Bullet	   *m_bullets[64]; 
	std::vector<Bullet*> m_bulletsv;
	std::queue<Bullet*> myQueue;
	EnemySpawn *m_spawn_up;
	EnemySpawn *m_spawn_down;
	EnemySpawn *m_spawn_left;
	EnemySpawn *m_spawn_right;

	enum E_Difficult { easy = g_maxEnemies/3, medium = (g_maxEnemies)/2, hard = g_maxEnemies } maxEnemies;
		   
	Assets *e_assets; // What does the e_ mean? See 'decl' for help! 
	int m_padding;	  // Padding + g_w are used to determine movement boundaries	

public:

	GameState(int a_padding, Assets *a_assets);
	~GameState();

	int GetPadding();

	void SpawnBullet(int a_x, int a_y, float a_speed, int direction);
	void SpawnEnemy(int a_x, int a_y);

	void Update(float a_dt);
	void Draw();

	void Play();

	Enemy  *GetEnemy(int i)	{ return m_enemy[i]; }
	Player GetPlayer()		{ return *m_player; }
	Shrine GetShrine()		{ return *m_shrine; }
	int GetScore()			{ return m_player->getScore(); }
	bool Lose()				{ return ( (m_player->getHealth() == 0) || (m_shrine->getHealth() == 0) ); }
};