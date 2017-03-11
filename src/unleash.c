/********************************************************          
 * unleash -- A lean shell program written from stracth.*
 *                                                      *   
 * Authors:  Sashank Beerappa Vanajakshi and			*
 *   		 Vinay Jagannath							*
 *                                                      *   
 * Purpose:  Project-1 CS551 - Fall 2016         		*   
 *                                                      *   
 * Usage:    Invoke the program from ash shell of minix.*   
 ********************************************************/ 
 
#include "unleash.h"

int main(int argc, char* argv[])
{
	char *cmdLine = NULL;
	char *cmd = NULL;
	char **cmdArgs = NULL;
	
	// Initialize environment
	InitializeShellEnvironment(argv[0]);

	while (1)
	{
		// Display prompt with current directory
		SetPrompt();
	
		// Read the command line for User input
		ReadCmd(&cmdLine);
		
		//Parse command line		
		ParseTheCommand(cmdLine);

		ScheduleCommand(cmd, cmdArgs);
		
		if(cmdLine != NULL)
		{
			free(cmdLine);
			cmdLine = NULL;
			cmd = NULL;
		}
	}
  
	return 0;
}

