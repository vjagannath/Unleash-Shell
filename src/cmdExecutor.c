#include "commonIncludes.h"

extern char **aliasList;
extern int aliasListSize;


int FindinAliasList(char *cmd)
{
	int i;
	//printf("Inside Find\n");
	for(i = 0; i < aliasListSize; i++)
	{
		if(strncmp(aliasList[i], cmd, strlen(cmd)) == 0)
		{
			//printf("Alias Found at %d\n", i);
			return i;	
		}
	}
	return -1;
}

void ExecuteCmd(char *cmd, char* cmdArgs[])
{
	pid_t childPid;
	int status, options = 0;
	int i;
	int foundIndex, tempIndex;
	char *resolvedCmd = NULL;
	int resolutionCount = 0;
	
	if((cmd != NULL) && (strlen(cmd) > 0))
	{
		//printf("Execute--- %s , len : %d", cmd, strlen(cmd));
		if ((foundIndex = FindinAliasList(cmd)) != -1)
		{
			resolvedCmd = strrchr(aliasList[foundIndex], '=');
			resolvedCmd++;
			resolutionCount++;
			
			//printf("resolved command %s\n", resolvedCmd);
			
			while(((tempIndex = FindinAliasList(resolvedCmd)) != -1) && (resolutionCount <= aliasListSize))
			{
				resolvedCmd = strrchr(aliasList[tempIndex], '=');
				resolvedCmd++;
				resolutionCount++;
			}
			
			if(resolutionCount <= aliasListSize)
				ExecuteCmd(resolvedCmd, cmdArgs);
			else
				printf("%s not found\n", cmd);
		}
		else if (strcmp(cmd, "exit") == 0)
		{
			DumpAliasList();
			exit(0);
		}
		else if(strcmp(cmd, "cd") == 0)
		{
			if(cmdArgs[1] != NULL)
			{
				if(chdir(cmdArgs[1]) != 0)
				{
					perror("");
				}
			}
		}
		else if(strcmp(cmd, "alias") == 0)
		{
			if(cmdArgs[1] != NULL)
			{
				if((foundIndex = FindinAliasList(cmdArgs[1])) != -1)
				{
					if(strlen(aliasList[foundIndex]) < strlen(cmdArgs[1]))
					{
						realloc(aliasList[foundIndex], strlen(cmdArgs[1]) + 1);
						strcpy(aliasList[aliasListSize], cmdArgs[1]);
					}
					else
					{
						strcpy(aliasList[aliasListSize], cmdArgs[1]);
					}
				}
				else
				{
					aliasList[aliasListSize] = (char *)malloc(strlen(cmdArgs[1]) + 1);
					strcpy(aliasList[aliasListSize], cmdArgs[1]);
					aliasListSize++;
					//printf("Added alias entry %s to list at %d", aliasList[aliasListSize-1],  aliasListSize-1);
				}
			}
		}
		else if(strcmp(cmd, "unalias") == 0)
		{
			if(cmdArgs[1] != NULL)
			{
				if((foundIndex = FindinAliasList(cmdArgs[1])) != -1)
				{
					for(i = foundIndex; i < aliasListSize-1; i++)
					{
						aliasList[i] = aliasList[i+1];
					}
					aliasList[aliasListSize-1] = NULL;
					aliasListSize--;
				}
			}
		}
		else
		{
			childPid = fork();
			if (childPid == -1)
			{
				perror("Cannot proceed. fork() error");
				exit(1);
			}
			else if (childPid == 0)
			{
				//This is Child
				if(execvp(cmd, cmdArgs) < 0)
				{
					perror("ERROR: exec failed ");
					exit(1);
				}
			}
			else
			{
				waitpid(childPid, &status, options);
				if (!WIFEXITED(status))
					printf("Child terminated abnormally.\n");
			}
		}
	}
}