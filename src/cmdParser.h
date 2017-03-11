#ifndef CMD_PARSER_H_
#define CMD_PARSER_H_

//Includes
#include "commonIncludes.h"

//Defines
#define DELIMITERS ",;|&"
#define MAX_ARGS 64
#define MAX_CMDS 64

//Global Variables

//Type Definitions
typedef struct _stack
{
	int top;
	int items[MAX_SIZE];
}stack;

//Function Declarations
void InitializeCommandStruct(int commandIndex);
void Push(stack *parenthesis, int element);
void Pop(stack *parenthesis);
int Peek(stack parenthesis);
int isEmpty(stack parenthesis);
int CheckForValidInput(char* input);
int CheckForValidParathesis(char* input);
void ParseIntoCommandList(char* inputString);
void PrepareArgumentsForCommands();
void PriotizeCommands();

#endif // CMD_PARSER_H_