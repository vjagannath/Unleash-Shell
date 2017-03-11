#ifndef COMMON_INCLUDES_H_
#define COMMON_INCLUDES_H_

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <setjmp.h>
//#include <pthread.h>

//Defines
#define  MAX_SIZE 64

//Type Definitions
typedef struct Cmd
{
	int priority;
	char delimiter;
	char* cmd;
	char* args;
	char** argList;
	int argCount;
}Command;

//Global Variables
Command CommandList[MAX_SIZE];
int commandCount;

//Common Function Delclaration
void DumpAliasList();

#endif // COMMON_INCLUDES_H_