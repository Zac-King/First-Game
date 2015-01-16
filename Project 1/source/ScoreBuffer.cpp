///////////////////////////////////////////////////////////////////////////////////////////////////////
//  Author  : Zac King  ///////////////////////////////////////////////////////////////////////////////
//  Origin  : Marco Salamone  /////////////////////////////////////////////////////////////////////////
//  Date    : 24/10/2014  /////////////////////////////////////////////////////////////////////////////
//  Purpose : Score Manager (Fstream save/sort/ load Score Data)  /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ScoreBuffer.h"
#include <fstream>

int ScoreBuffer::m_nScores;
ScoreData *ScoreBuffer::m_scores;
const char *ScoreBuffer::m_path = "scores.dat";

// Load the Doc  //////////////////////////////////////////////////////////////////////////////////////
void ScoreBuffer::load()
{
	std::fstream fin;
	fin.open(m_path, std::ios_base::binary | std::ios_base::in);
	if (fin.is_open())
	{
		fin >> m_nScores;
		m_scores = new ScoreData[m_nScores];
		fin.read((char*)m_scores, sizeof(ScoreData)*m_nScores);
	}
	fin.close();
}
// Draw the Doc  //////////////////////////////////////////////////////////////////////////////////////
void ScoreBuffer::draw(int a_x, int a_y)
{
	// If there is nothing to draw, Draw nothing
	if (m_nScores == 0)return;
	
	sort();

	for (int i = 0; i < m_nScores && i < 12; i++)
	{
		char c_score[8];
		itoa(m_scores[i].score, c_score, 10);

			//DrawString(m_scores[i].name, a_x, a_y - (i * 40));
		DrawString(c_score, g_w / 2 + 32, a_y - (i * 40));
	}
}
// Draw the Highest Score :  Score[0]  ////////////////////////////////////////////////////////////////
void ScoreBuffer::drawHigh(int a_x, int a_y)
{
	if (m_nScores == 0)return;
	// sort first to be sure c_score[0] is the highest score
	sort();

	char c_score[8];
	itoa(m_scores[0].score, c_score, 10);

	DrawString(c_score, a_x, a_y );
}
// Save Scores to the doc  ////////////////////////////////////////////////////////////////////////////
void ScoreBuffer::save()
{
	std::fstream fout;
	fout.open(m_path, std::ios_base::binary | std::ios_base::out);
	// Open Doc for writing to
	if (fout.is_open())
	{
		// Putting info on the doc
		fout << m_nScores;
		fout.write((char*)m_scores, sizeof(ScoreData)*m_nScores);
		// Once info is stored on doc stored, clear the pointers. No leaks Hatsune Miku! 
		delete[] m_scores;
		m_scores = nullptr;
		m_nScores = 0;
	}
	// Be sure to close the door on the way out
	fout.close();
}
// Comparing the scores ///////////////////////////////////////////////////////////////////////////////
bool ScoreComp(ScoreData a, ScoreData b)
{ return (a.score < b.score); }
// Swapping the scores  ///////////////////////////////////////////////////////////////////////////////
void ScoreSwap(ScoreData &a, ScoreData &b)
{ ScoreData t; t = a; a = b; b = t; }
// Sorting the Scores  ////////////////////////////////////////////////////////////////////////////////
void ScoreBuffer::sort()
{
	// Double loop to sort 
	// value is compared with all the rest, then we move to the next value and check it against the rest
	for(int j = 0; j < m_nScores; ++j)
	{
		for (int i = 0; i < m_nScores - 1; ++i)
		{
			if (ScoreComp(m_scores[i], m_scores[i + 1]))
				ScoreSwap(m_scores[i], m_scores[i + 1]);
		}
	}
}
// Add a score to the document  ///////////////////////////////////////////////////////////////////////
void ScoreBuffer::addScore(ScoreData a_score)
{
	// Temp poiter for function
	ScoreData *old_scores = m_scores;
	m_scores = new ScoreData[m_nScores + 1];
	// Placing the cursor at the end of the doc
	for (int i = 0; i < m_nScores; i++)
	m_scores[i] = old_scores[i];
	// Delete Pointer
	delete[] old_scores;
	// Add the new score to the end of the doc
	m_scores[m_nScores] = a_score;
	// Incrament the number of scores
	m_nScores++;
}