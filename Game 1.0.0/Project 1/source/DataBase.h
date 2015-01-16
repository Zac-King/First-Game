#include "Decl.h"
#include "sqlite3.h"
#include <iostream>
#include <string>
#include <sstream>
#pragma once

enum e_Command {
	eCommand_Move_Left, eCommand_Move_Down,
	eCommand_Move_Right, eCommand_Move_Up,
	eCommand_Fire, eCommand_Lock, eNone_Selected, 
	
	e_Count
};

class ControlsDataBase
{
	e_Command selctedCommand;
	static char *s_filename;
	static sqlite3 *m_dataBase;
	static const char s_keys_defualt[e_Count];
	static const char s_key_cache[e_Count];
	static char keys[e_Count];
	ControlsDataBase();

public:
	static void ChangeControl(char a_newControl, e_Command &a_command) { keys[a_command] = a_newControl; }
	static bool IsKeyDown(e_Command a_command) { return ::IsKeyDown(keys[a_command]); }

	static int CheckIfTableExists(void* ext, int numArgs, char **data, char **columnName) { ext = (void*)(bool)numArgs; return 0; }

	static void Open();
	static void Close()						   { sqlite3_close(m_dataBase); }
	static void Draw();
	static void Initialize();
};