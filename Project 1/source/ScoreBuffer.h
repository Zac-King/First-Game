///////////////////////////////////////////////////////////////////////////////////////////////////////
//  Author  : Zac King  ///////////////////////////////////////////////////////////////////////////////
//  Origin  : Zac King  ///////////////////////////////////////////////////////////////////////////////
//  Date    : 24/10/2014  /////////////////////////////////////////////////////////////////////////////
//  Purpose : Score Manager Header  ///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Aie.h"
#include "Decl.h"

struct ScoreData
{
	int score;
		//char name[16];
};

class ScoreBuffer
{
	static int m_nScores;		// Number of scores
	static ScoreData *m_scores;	// Array of scores
	static const char *m_path;	// Save Doc Name
public:
	static void load();						// Load all scores
	static void draw(int a_x, int a_y);		// Draw Highscore page
	static void drawHigh(int a_x, int a_y); // Draw only the Highest score
	static void save();						// Save highscore
	static void sort();						// Sort values, Highests to lowest
	static void addScore(ScoreData a_score);// Add a new score to the Doc
	static void Close();
};