///////////////////////////////////////////////////////////////////////////////////////////////////////
//  Author  : Zac King  ///////////////////////////////////////////////////////////////////////////////
//  Origin  : Marco Salamone  /////////////////////////////////////////////////////////////////////////
//  Date    : 24/10/2014  /////////////////////////////////////////////////////////////////////////////
//  Purpose : Gamestate (Manage all objects in Game (Update/Draw)  ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GameState.h"
#include "Player.h"
#include "Assets.h"
#include "Bullet.h"
#include "Enemy.h"
#include "ScoreBuffer.h"
#include <random>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;

// Get object collision padding  //////////////////////////////////////////////////////////////////////
int GameState::GetPadding() { return m_padding; }
// Constructor  ///////////////////////////////////////////////////////////////////////////////////////
GameState::GameState(int a_padding, Assets *a_assets)
{
	maxEnemies = easy;
	m_padding = a_padding;
	e_assets  = a_assets;
	unsigned int m_BackGround_sprite = e_assets->Get(eBackground);
	// Create Player
	m_player = new Player(this, e_assets->Get(ePlayer), g_w/2, 40, 32, 32, 200, 0.21f);
	// Create Shrine
	m_shrine = new Shrine(this, e_assets->Get(eShrine), g_w/2, g_h/2, 32, 48);
	// Create Bullets && set all to Null
			//for (int i = 0; i < g_maxBullets; ++i)
				//m_bullets[i] = nullptr;



	// Create Eneimies && set all to Null
	for (int i = 0; i < g_maxEnemies; ++i)
		m_enemy[i] = nullptr;
	// Create Spawners
	m_spawn_up    = new EnemySpawn(this, e_assets->Get(eSpawner), g_w / 2,  32, 32, 32, 200, 0.45f, eLeft);
	m_spawn_down  = new EnemySpawn(this, e_assets->Get(eSpawner), g_w / 2, 570, 32, 32, 200, 0.45f, eRight);
	m_spawn_left  = new EnemySpawn(this, e_assets->Get(eSpawner), 32,  g_h / 2, 32, 32, 200, 0.45f, eDown);
	m_spawn_right = new EnemySpawn(this, e_assets->Get(eSpawner), 750, g_h / 2, 32, 32, 200, 0.45f, eUp);

	e_GState currentState = eMainMenu;
	e_GState rootState = eMainMenu;
}
// Update game  ///////////////////////////////////////////////////////////////////////////////////////
void GameState::Update(float a_dt)
{
	// Update Player
	if (m_player) m_player->Update(a_dt);
	// Update Shrine
	if (m_shrine) m_shrine->Update(a_dt);
	// Update Enemies
	for (int i = 0; i < maxEnemies; ++i)
		if (m_enemy[i])
		{
		m_enemy[i]->Update(a_dt);
		}
	// Update Bullets
			//for (int i = 0; i < g_maxBullets; ++i)
				//if (m_bullets[i])
					//m_bullets[i]->Update(a_dt);
	auto it = m_bulletsv.begin();
	while (it != m_bulletsv.end())
	{
		(*it)->Update(a_dt);
		it++;
	}

	it = m_bulletsv.begin();
	while (it != m_bulletsv.end())
	{
		if (!(*it)->IsActive())
		{
			delete *it;
			it = m_bulletsv.erase(it);
		}
		else it++;
	}

	while (!myQueue.empty())
	{
		m_bulletsv.push_back(myQueue.front());
		myQueue.pop();
	}
	// Update spawners
 	m_spawn_up   ->Update(a_dt);
	m_spawn_down ->Update(a_dt);
	m_spawn_left ->Update(a_dt);
	m_spawn_right->Update(a_dt);
	// Check if enemies are still Active
	for (int i = 0; i < maxEnemies; ++i)
	{
		if (m_enemy[i] && !m_enemy[i]->IsActive())
		{ delete m_enemy[i]; m_enemy[i] = nullptr; }
	}
	// Check if Bullets are still Active
			//for (int i = 0; i < g_maxBullets; ++i)
				//if (m_bullets[i] && !m_bullets[i]->IsActive())
				//{ delete m_bullets[i]; m_bullets[i] = nullptr; }
}
// Draw Game  /////////////////////////////////////////////////////////////////////////////////////////
void GameState::Draw()
{
	// Draw BackGround
	DrawSprite(backgroundSprite);
	MoveSprite(backgroundSprite, g_w / 2, g_h / 2);
	// Draw Score
	{
		char output[16] = "Score : ";
		char c_score[8];
		itoa(m_player->getScore(), c_score, 10);
		strcat_s(output, 16, c_score);
		DrawString(output, g_w/2 + 128, g_h - 35);
		// Draw High Score
		ScoreBuffer::drawHigh(g_w / 2 + 225, g_h - 10);
	}
	// Draw Health
	{
		// char output[16] = "Health: ";
		// char c_score[8];
		// itoa(m_player->getHealth(), c_score, 10);
		// strcat_s(output, 16, c_score);
		// DrawString(output, 32, g_h );

		int healthBar = m_player->getHealth() / 5;
		for (int i = 0; i < healthBar; ++i)
		{
			int temp = 32 + (i * 8);
			MoveSprite(healthBar_sprite, temp, 665);
			DrawSprite(healthBar_sprite);
		}
	}
	// Draw Shrine Health
	{
		// char output[32] = "Shrine Health: ";
		// char c_score[8];
		// itoa(m_shrine->getHealth(), c_score, 10);
		// strcat_s(output, 32, c_score);
		// DrawString(output, 32, g_h - 30);

		int healthBar = m_shrine->getHealth() / 5;
		for (int i = 0; i < healthBar; ++i)
		{
			int temp = 32 + (i * 8);
			MoveSprite(shrine_healthBar_sprite, temp, 632);
			DrawSprite(shrine_healthBar_sprite);
		}
	}
	
	// Draw Shrine				Temp (Will not be drawn in final)
			//if (m_shrine) m_shrine->Draw();
	// Draw Player
	if (m_player) m_player->Draw();
	// Draw Bullets
			//for (int i = 0; i < g_maxBullets; ++i)
				//if (m_bullets[i])
					//m_bullets[i]->Draw();

	auto it = m_bulletsv.begin();
	while (it != m_bulletsv.end())
	{						
		if ((*it)->IsActive())
			(*it)->Draw();

		it++;
	}

	// Draw Enemies
	for (int i = 0; i <maxEnemies; ++i)
		if (m_enemy[i])
			m_enemy[i]->Draw();
	// Draw Spawners ....		Temp (Will not be drawn in final)
			//m_spawn_up   ->Draw();
			//m_spawn_down ->Draw();
			//m_spawn_left ->Draw();
			//m_spawn_right->Draw();
}
// Spawn Bullet  //////////////////////////////////////////////////////////////////////////////////////
void GameState::SpawnBullet(int a_x, int a_y, float a_speed, int direction)
{
	// Spawn Bullet when viable
			//  for (int i = 0; i < g_maxBullets; ++i)
			//	if (!m_bullets[i] || !m_bullets[i]->IsActive()) 
			//	{
			//		if (m_bullets[i] && !m_bullets[i]->IsActive())
			//		{ delete m_bullets[i]; m_bullets[i] = nullptr; }
			//		// Create a enemy bullet in the object array
			//		m_bullets[i] = new Bullet(this, e_assets->Get(eShot), a_x, a_y, 10, 14, a_speed, direction);
			//		return;
			//	}
	myQueue.push(new Bullet(this, e_assets->Get(eShot), a_x, a_y, 10, 14, a_speed, direction));
	int i = 1;
	try
	{
		if (i = 1)
			throw i;
	}

	catch (int e)
	{
		cout << "Fire Bolt!!!!!" << endl;
	}
}
// Spawn Enemy  ///////////////////////////////////////////////////////////////////////////////////////
void GameState::SpawnEnemy(int a_x, int a_y)
{
	// Difficulty Switch  
	if (m_player->getScore() < 150) maxEnemies = medium;
	if (m_player->getScore() < 300) maxEnemies = hard;
	// Create a new Enemy when needed  
	for (int i = 0; i < maxEnemies; ++i)
			if (!m_enemy[i] || !m_enemy[i]->IsActive())
			{
				if (m_enemy[i] && !m_enemy[i]->IsActive())
				{ delete m_enemy[i]; m_enemy[i] = nullptr; }
				// Create a new Enemy in the object array
				m_enemy[i] = new Enemy(e_assets->Get(eEnemy), a_x, a_y, 32, 32, 150, 0.15f, m_player);
				return;
			}
}
// De-Constructor  ////////////////////////////////////////////////////////////////////////////////////
GameState::~GameState()
{
	// Delete the Player
	delete m_player;
	// Delete the Shrine
	delete m_shrine;
	// Delete the Spawners
	delete m_spawn_up;
	delete m_spawn_down;
	delete m_spawn_left;
	delete m_spawn_right;
	// Delete all the Enemies
	for (int i = 0; i < maxEnemies; ++i)
		if (m_enemy[i])
		{ delete m_enemy[i]; m_enemy[i] = nullptr; }
	// Delete all the Bullets
			//for (int i = 0; i < g_maxBullets; ++i)
				//if (m_bullets[i])
				//{ delete m_bullets[i];  m_bullets[i] = nullptr; }
	
	m_bulletsv.clear();

}