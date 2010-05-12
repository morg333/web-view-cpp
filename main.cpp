
/*! @file main.cpp
 * @brief Main file. Contains the Program Entry Point
 */

#include "version.h"
#include "includes.h"
#include "main_class.h"

VERSION getAppVersion() {
	return(VERSION((int)VERSION_MAJOR, (int)VERSION_MINOR, (int)VERSION_PATCH));
}


/*********************************************************************//*!
 * @brief Program entry
 * 
 * @param argc Command line argument count.
 * @param argv Command line argument strings.
 * @return 0 on success
 *//*********************************************************************/
int main(int argc, char ** argv) {
	CMain main;
	OSC_ERR err=main.Init(argc, argv);
	if(err!=SUCCESS) return(1);
	
	err=main.MainLoop();
	
	return(err);
}
