///////////////////////////////////////////////////////////////////////////////////////////////////////
//  Author  : Zac King  ///////////////////////////////////////////////////////////////////////////////
//  Origin  : Marco Salamone  /////////////////////////////////////////////////////////////////////////
//  Date    : 5/12/2014  //////////////////////////////////////////////////////////////////////////////
//  Purpose : Manage user input controls  /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ControlsDatabase.h"
#include <cstring>
#include <sstream>
#include <iostream>

const char  ControlManager::s_keys_default[e_count] = {'A','D','W','S',' ', 'L'};
	  char  ControlManager::s_keys_cache[e_count];
	  char *ControlManager::s_filename = "Controls.db";
   sqlite3 *ControlManager::s_db;
// Close the Database  ////////////////////////////////////////////////////////////////////////////////
void ControlManager::close() 
{ sqlite3_close(s_db); }
// Check command key based on Database  ///////////////////////////////////////////////////////////////
bool ControlManager::isKeyDown(e_Controls e)
{
	//std::cout << s_keys_cache[e] << " " << e << std::endl;
		
	return IsKeyDown(s_keys_cache[e]);
	//return 1;
}
// ---  ///////////////////////////////////////////////////////////////////////////////////////////////
static int FetchControls(void *key_cache, int numArgs, char **data, char**name)
{
	for (int i = 0; i < numArgs; i+=2)
	{
		((char*)key_cache)[atoi(data[i + 1])] = atoi(data[i]);
	}
	return 0;
}
// Check if Table exist  //////////////////////////////////////////////////////////////////////////////
static int TableExists(void *doesExist, int numArgs, char **data, char **name)
{
	*(bool*)doesExist = numArgs;
	return 0;
}
// Open DataBase and assign defualt if does not exist  ////////////////////////////////////////////////
void ControlManager::open()
{
	sqlite3_open(s_filename, &s_db);

	const char* command = "SELECT * FROM controls;";
	bool exists = false;
	//std::cerr << sqlite3_exec(s_db, command, TableExists, &exists, 0) << std::endl;

	if (exists)
	{
		//std::cerr << "Exists" << std::endl;
		const char* command = "SELECT * FROM controls;";
		//std::cerr << sqlite3_exec(s_db, command, FetchControls, s_keys_cache, 0) << std::endl;

		for (int i = 0; i < e_count; ++i)
		{
			std::stringstream ss;
			ss << "INSERT INTO controls(key,command) VALUES (";
			ss << (int)s_keys_cache[i] << "," << i << ");";

			//std::cerr << sqlite3_exec(s_db, ss.str().c_str(), 0, 0, 0) << std::endl;
		}
	}
	else
	{
		//std::cerr << "Doesn't Exist" << std::endl;
		memcpy(s_keys_cache, s_keys_default, e_count * sizeof(char));
		
		const char* command = "CREATE TABLE controls(key INT, command INT);";
		//std::cerr << sqlite3_exec(s_db, command, 0, 0, 0) << std::endl;
	
		for (int i = 0; i < e_count; ++i)
		{
			std::stringstream ss;
			ss << "INSERT INTO controls(key,command) VALUES (";
			ss << (int)s_keys_default[i] << "," << i << ");";

			//std::cerr << sqlite3_exec(s_db, ss.str().c_str(), 0, 0, 0) << std::endl;
		}
	}
}
// Change Command Key in the DataBase  ////////////////////////////////////////////////////////////////
 void ControlManager::changeKey()
{
	int e = -1;
	do
	{
		system("CLS");
		std::cout << "Which control do you want to change? \n0.) Left \n1.) Right \n2.) Up \n3.) Down \n4.) Fire \n5.) Lock" << std::endl;
		std::cin >> e;
	} while ((e > 5) && (e < 0));
	char key = ' ';
	do
	{
		system("CLS");
		std::cout << "What key would you like to use to ";
		switch (e)
		{
		case e_left:	{std::cout << "Left movement?\n";			break; }
		case e_right:	{std::cout << "Right movement?\n";			break; }
		case e_up:		{std::cout << "Up movement?\n";				break; }
		case e_down:	{std::cout << "Down movement?\n";			break; }
		case e_lock:	{std::cout << "Lock firing direction?\n";	break; }
		case e_fire:	{std::cout << "Fire?\n";					break; }
		}
		std::cin >> key;
	} while (key >= 128 || key <= 31);
	system("CLS");

	key = toupper(key);
	s_keys_cache[e] = key;
	std::cout << "Control change sucessful\n";
	 std::stringstream ss;
	 ss << "UPDATE controls SET key = " << (int)key << " WHERE command = " << e << ";";
	 sqlite3_exec(s_db, ss.str().c_str(), 0, 0, 0);
}
 ///////////////////////////////////////////////////////////////////////////////////////////////////////
 void ControlManager::changeState()
 {

 }
 // Draw Controls to screen  ///////////////////////////////////////////////////////////////////////////
 void ControlManager::DrawControl(e_Controls e, int a_x, int a_y)
 {
	 char out[2] = { s_keys_cache[e], '\0' };
	 switch (e)
	 {
	 case e_left:	{DrawString("Left: ", a_x, a_y);	DrawString(out, a_x + 90, a_y); break; }
	 case e_right:	{DrawString("Right: ", a_x, a_y);	DrawString(out, a_x + 90, a_y); break; }
	 case e_up:		{DrawString("Up: ", a_x, a_y);		DrawString(out, a_x + 90, a_y); break; }
	 case e_down:	{DrawString("Down: ", a_x, a_y);	DrawString(out, a_x + 90, a_y); break; }
	 case e_lock:	{DrawString("Lock: ", a_x, a_y);	DrawString(out, a_x + 90, a_y); break; }
	 case e_fire:	
	 {
		DrawString("Fire: ", a_x, a_y);
		if (s_keys_cache[e] == ' ')
			DrawString("SpaceBar", a_x + 90, a_y);
		DrawString(out, a_x, a_y);
		break; }
	 }
 }