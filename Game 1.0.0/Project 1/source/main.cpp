///////////////////////////////////////////////////////////////////////////////////////////////////////
//  Author  : Zac King  ///////////////////////////////////////////////////////////////////////////////
//  Origin  : Marco Salamone / Zac King  //////////////////////////////////////////////////////////////
//  Date    : 24/10/2014  /////////////////////////////////////////////////////////////////////////////
//  Purpose : Declaration Header  /////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(OSX)
	#include <crtdbg.h>
#endif
#include "Decl.h"
#include "GameState.h"
#include "Assets.h"
#include "Enemy.h"
#include "Player.h"
#include "ScoreBuffer.h"
#include "ControlsDatabase.h"
#include <math.h>
#include "iostream"
#include <string>
#include "sqlite3.h"

int main(int argc, char* argv[])
{
	
	Initialise(g_w, g_h, false, "Spirit's Defence");
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));
	
	// Declare assets
	/////////////////////////////////////////////////////////////////////
	Assets *assets = new Assets;
	assets->LoadSprite("./images/Player_Sprite.png",	    32,  32, ePlayer);
	assets->LoadSprite("./images/Enemy_Sprite.png",		    32,  32, eEnemy);
	assets->LoadSprite("./images/Bullet_TestSprite.png",     8,   8, eShot);
	assets->LoadSprite("./images/Spawner_TestSprite.png",   16,  16, eSpawner);
	assets->LoadSprite("./images/Shrine_TestSprite.png",    32,  48, eShrine);
	assets->LoadSprite("./images/BackGround_Sprite.png",   790, 680, eBackground);
	assets->LoadSprite("./images/BackGround_Blank.png",	   790, 680, eBackGround_B);
	assets->LoadSprite("./images/BackGround_MainMenu.jpg", 790, 680, eBackGround_MM);
	unsigned int BackGround_MM_sprite = assets->Get(eBackGround_MM);
	unsigned int BackGround_B_sprite = assets->Get(eBackGround_B);
	// Set Starting Values 
	/////////////////////////////////////////////////////////////////////
	GameState *myGame = new GameState(20, assets);
	e_GState currentState = eMainMenu;
	e_GState rootState = eMainMenu;
	bool isRunning = true;
	ControlManager::open();
	// Load Score Doc
	ScoreBuffer::load();
	/////////////////////////////////////////////////////////////////////
	// Game Loop  /////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	do
	{
		ClearScreen();
		float dt = GetDeltaTime();
			// Gamestate switch
			switch (currentState)
			{
				// Main Menu  ///////////////////////////////////////////////////////
				case eMainMenu:
				{
					MoveSprite(BackGround_MM_sprite, g_w / 2, g_h / 2);
					DrawSprite(BackGround_MM_sprite);					
					DrawString("[G]ame",     g_w / 2 - 60, g_h - 120);
					DrawString("[H]igh Scores",    g_w / 2 - 60, g_h - 240);
					DrawString("[C]ontrols", g_w / 2 - 60, g_h - 360);
					DrawString("[E]xit",     g_w / 2 - 60, g_h - 480);
					if (IsKeyDown('G')) { currentState = eGame;    rootState = eMainMenu; }
					if (IsKeyDown('H')) { currentState = eScore;   rootState = eMainMenu; }
					if (IsKeyDown('C')) { currentState = eControl; rootState = eMainMenu; }
					if (IsKeyDown('E')) { currentState = eExit;    rootState = eMainMenu; }
				} break;
				// Controls  ////////////////////////////////////////////////////////
				case eControl:
				{
					DrawSprite(BackGround_B_sprite);
					MoveSprite(BackGround_B_sprite, g_w / 2, g_h / 2);
					// Draw Movement controls
					DrawString("Move:",    120, g_h - 60);	
					ControlManager::DrawControl(e_left, 180, g_h - 100);
					ControlManager::DrawControl(e_right, 180, g_h - 130);
					ControlManager::DrawControl(e_up, 180, g_h - 160);
					ControlManager::DrawControl(e_down, 180, g_h - 190);
					// Draw fire controls
					DrawString("Weapon:", 90, g_h - 245);	
					ControlManager::DrawControl(e_fire, 180, g_h - 285);
					ControlManager::DrawControl(e_lock, 180, g_h - 315);
					DrawString("Change control     [V]", 180, g_h - 475);
					DrawString("Pause: p", 180, g_h - 395);
					DrawString("[B]ack", g_w - 180, 90);
					if (IsKeyDown('V')) { currentState = eControlChange; }
					if (IsKeyDown('B')) { currentState = rootState; }
				} break;

				case eControlChange:
				{
					DrawSprite(BackGround_B_sprite);
					MoveSprite(BackGround_B_sprite, g_w / 2, g_h / 2);
					DrawString("See command screen", g_w / 2 - 95, g_h - 70);
					DrawString("[B]ack", g_w / 2 - 180, 90);
					FrameworkUpdate();
					ControlManager::changeKey(); 
					currentState = eControl;
				}break;

				// In Game Pause Screen  ////////////////////////////////////////////
				case ePause:
				{
					DrawSprite(BackGround_B_sprite);
					MoveSprite(BackGround_B_sprite, g_w / 2, g_h / 2);
					DrawString("[Game Paused]",		g_w / 2 - 95, g_h - 70);
					DrawString("[H]igh Scores",		g_w / 2 - 60, g_h - 180);
					DrawString("[C]ontrols",        g_w / 2 - 60, g_h - 280);
					DrawString("[E]xit",            g_w / 2 - 60, g_h - 380);
					DrawString("[B]ack",		    g_w - 180, 90);
					if (IsKeyDown('H')) { currentState = eScore;    rootState = ePause; }
					if (IsKeyDown('C')) { currentState = eControl;  rootState = ePause; }
					if (IsKeyDown('E')) { currentState = eExit; }
					if (IsKeyDown('B')) { currentState = eGame; }
				} break;
				// Top 12 HighScores  ///////////////////////////////////////////////
				case eScore:
				{
					DrawSprite(BackGround_B_sprite);
					MoveSprite(BackGround_B_sprite, g_w / 2, g_h / 2);
					DrawString("High Scores", g_w/2 - 80, g_h-40);
					ScoreBuffer::draw(300, g_h - 120);
					DrawString("[B]ack", g_w - 180, 90);
					if (IsKeyDown('B')) { currentState = rootState; }
				}break;
				// Game  ////////////////////////////////////////////////////////////
				case eGame:
				{	
					if (IsKeyDown('P')) { currentState = ePause; rootState = eGame; }
					myGame->Update(dt);
					myGame->Draw();
					if (myGame->Lose())
					{
						ScoreData temp;
						temp = {myGame->GetScore()};
						ScoreBuffer::addScore(temp);
						currentState = eLost;
					}
				} break;
				// Lost State  //////////////////////////////////////////////////////
				case eLost:
				{
					DrawSprite(BackGround_B_sprite);
					MoveSprite(BackGround_B_sprite, g_w / 2, g_h / 2);
					DrawString("You Lost", g_w / 2 - 60, g_h - 180);
					DrawString("[M]ain Menu", g_w / 2 - 60, g_h - 310);
					DrawString("[T]ry Again", g_w / 2 - 60, g_h - 380);
					DrawString("[H]igh Scores", g_w / 2 - 60, g_h - 450);
					DrawString("[E]xit", g_w / 2 - 60, g_h - 520);
					if (IsKeyDown('E')) { currentState = eExit; }
					if (IsKeyDown('H')) { currentState = eScore;    rootState = eLost; }
					if (IsKeyDown('M') || IsKeyDown('T'))
					{ 
						delete myGame;
						myGame = new GameState(20, assets);
						if (IsKeyDown('M'))
							currentState = eMainMenu; 
						if (IsKeyDown('T'))
							currentState = eGame;
					}
				} break;
				// Game Exit  ///////////////////////////////////////////////////////
				case eExit:
				{ isRunning = false; } break;
			}
	} while (FrameworkUpdate() == false && isRunning);
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// Saving/Closing Doc
	ScoreBuffer::save();
	// Deleting Game
	delete myGame;
	ControlManager::close();
	Shutdown();
	// This was a triumph!
	// I'm making a note here, HUGE SUCCESS!
	return 0;
}