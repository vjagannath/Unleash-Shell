#ifndef UNLEASH_H_
#define UNLEASH_H_

//Includes
#include "commonIncludes.h"

//Defines

//Global Variables
char **aliasList;
int aliasListSize;

//Type Definitions

//Function Declarations
int InitializeShellEnvironment(char *progPath);
void SetPrompt();
void ReadCmd(char **cmdLine);
void ParseTheCommand(char* inputString);
void ParseCmd(char *cmdLine, char **cmd, char **cmdArgs[]);
void ScheduleCommand(char* cmd, char** cmdArgs);

#endif // UNLEASH_H_
