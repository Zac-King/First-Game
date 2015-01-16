#include "DataBase.h"

const char ControlsDataBase::s_keys_defualt[e_Count] = { 'A', 'S', 'D', 'W', ' ', 'L', };
const char ControlsDataBase::s_key_cache[e_Count];
sqlite3 *ControlsDataBase::m_dataBase;
char *ControlsDataBase::s_filename = "Controls.db";
char ControlsDataBase::keys[e_Count];

void ControlsDataBase::Open()
{
	sqlite3_open(s_filename, &m_dataBase);

	sqlite3 *db = m_dataBase;

	const char *sqlStatement = "SELECT name FROM sqlite_master WHERE type = 'table' AND name = 'CONTROLS'";
	bool tableExists;
	sqlite3_exec(db, sqlStatement, CheckIfTableExists, &tableExists, 0);

	if (!tableExists)
	{
		const char *sqlStatement = "CREATE CONTROLS IF NOT EXISTS ( KEY INT, NAME INT);";
		sqlite3_exec(db, sqlStatement, 0, 0, 0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
ControlsDataBase::ControlsDataBase()
{
	selctedCommand = eNone_Selected;
	if (!m_dataBase)
	{
		m_dataBase = NULL;
		sqlite3_open("Controls.db", &m_dataBase);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void ControlsDataBase::Initialize()
{
	sqlite3 *db = m_dataBase;
	//std::cout << sqlite3_open("random.db", &db) << std::endl;


	const char *sqlStatement = "SELECT name FROM sqlite_master WHERE type = 'table' AND name = 'CONTROLS'";
	bool tableExists;
	sqlite3_exec(db, sqlStatement, CheckIfTableExists, &tableExists, 0);
	if (!tableExists)
	{
		const char *sqlStatement = "CREATE CONTROLS IF NOT EXISTS ( KEY INT, NAME INT);";
		sqlite3_exec(db, sqlStatement, 0, 0, 0);

		std::stringstream SS;
		SS << "INSERT INTO CONTROLS( KEY INT, NAME INT) VALUES (" << (int)'a' << ", " << eCommand_Move_Left  << ");\n";
		SS << "INSERT INTO CONTROLS( KEY INT, NAME INT) VALUES (" << (int)'d' << ", " << eCommand_Move_Right << ");\n";
		SS << "INSERT INTO CONTROLS( KEY INT, NAME INT) VALUES (" << (int)'w' << ", " << eCommand_Move_Up	 << ");\n";
		SS << "INSERT INTO CONTROLS( KEY INT, NAME INT) VALUES (" << (int)'s' << ", " << eCommand_Move_Down  << ");\n";
		SS << "INSERT INTO CONTROLS( KEY INT, NAME INT) VALUES (" << (int)' ' << ", " << eCommand_Fire		 << ");\n";
		SS << "INSERT INTO CONTROLS( KEY INT, NAME INT) VALUES (" << (int)'l' << ", " << eCommand_Lock		 << ");\n";
		sqlite3_exec(db, SS.str().c_str(), 0, 0, 0);

	}

	else
	{

	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void ControlsDataBase::Draw()
{
	char temp[e_Count];


	DrawString("Left:  ", g_w / 4 - 60, g_h - 80 );
	DrawString("Right: ", g_w / 4 - 60, g_h - 120);
	DrawString("Up:    ", g_w / 4 - 60, g_h - 160);
	DrawString("Down:  ", g_w / 4 - 60, g_h - 200);
	DrawString("Fire:  ", g_w / 4 - 60, g_h - 240);
	DrawString("Lock:  ", g_w / 4 - 60, g_h - 280);
}