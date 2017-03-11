#include "cmdScheduler.h"


void ScheduleCommand()
{	
	int commandIndex, argIndex;
	
	for(commandIndex = 0; commandIndex <= commandCount ; commandIndex++)
	{		
		if((CommandList[commandIndex].cmd != NULL) && 
			(CommandList[commandIndex].argList != NULL))
		{
			ExecuteCmd(CommandList[commandIndex].cmd, CommandList[commandIndex].argList);
			
			free(CommandList[commandIndex].cmd);
			
			for(argIndex=0; argIndex < CommandList[commandIndex].argCount; argIndex++)
			{
				if(CommandList[commandIndex].argList[argIndex] != NULL)
				{
					free(CommandList[commandIndex].argList[argIndex]);
				}
			}
			
			free(CommandList[commandIndex].argList);
		}			
	}
}