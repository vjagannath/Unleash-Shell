#include "cmdParser.h"


void ParseCmd(char *cmdLine, char ** cmd, char **cmdArgs[])
{
	char *arg = NULL;
	int argCount = 0;
	
	
	*cmd = strtok(cmdLine, " \t\n");
	
	//printf("Here\n");
	
	if(*cmd != NULL)
	{
		//printf("There\n");
		//By default first arg is name of program itself
		(*cmdArgs) = (char**)malloc(sizeof(char**)*MAX_ARGS);
		(*cmdArgs)[argCount] = (char*) malloc(strlen(*cmd)+1);
		
		strcpy((*cmdArgs)[argCount], *cmd);
		printf("\narg[%d]:%s", argCount, (*cmdArgs)[argCount]);
		
		arg = strtok(NULL, " \t\n");				
		while(arg != NULL)
		{
			argCount++;
			
			(*cmdArgs)[argCount] = (char*) malloc(strlen(arg)+1);
			strcpy((*cmdArgs)[argCount], arg);
			printf("\narg[%d]:%s", argCount, (*cmdArgs)[argCount]);
			
			arg = strtok(NULL, " \t\n");	
		}
		
		argCount++;
		(*cmdArgs)[argCount] = NULL;
		printf("\narg[%d]:%s", argCount, (*cmdArgs)[argCount]);
	}
	
	//printf("Parse--- %s , len : %d", *cmd, strlen(*cmd));
}


void InitializeCommandStruct(int commandIndex)
{
	Command* oneCommand = &(CommandList[commandIndex]);
	oneCommand->cmd = (char*)malloc(MAX_CMDS * sizeof(char));
	oneCommand->args = (char*)malloc(512 * sizeof(char));
	oneCommand->delimiter = '\0';
	oneCommand->priority = 0;
	oneCommand->argCount = 0;
}

void Push(stack *parenthesis, int element)
{
	if (parenthesis->top < MAX_SIZE-1)
	{
		parenthesis->top = parenthesis->top + 1;
		parenthesis->items[parenthesis->top] = element;
	}
}

void Pop(stack *parenthesis)
{
	if (parenthesis->top >= 0)
	{
		parenthesis->top = parenthesis->top - 1;
	}
}

int Peek(stack parenthesis)
{
	if (parenthesis.top<0)
	{
		return 0;
	}
	return parenthesis.items[parenthesis.top];
}

int isEmpty(stack parenthesis)
{
	if (parenthesis.top <0)
		return 1;
	return 0;
}

int CheckForValidInput(char* input)
{
	// Check if the input command string starts and ends properly
	int index = 0;
	while( input[index] == ' ' )
	{
		index++;
	}
	if(input[index] == ',' || input[index] == ';' || input[index] == '|' || input[index] == '&')
	{
		return 0;
	}
	while (input[index] != '\0')
	{
		index++;
	}
	index--;
	if (input[index] == ',' || input[index] == ';' || input[index] == '|' || input[index] == '&')
	{
		return 0;
	}
	return 1;
}

int CheckForValidParathesis(char* input)
{
	if (!CheckForValidInput(input))
	{
		return 0;
	}

	stack parathesisStack;
	char temp;
	parathesisStack.top = -1;

	for(int i = 0 ; input[i] != '\0'; i++)
	{
		if( input[i] == '(')
		{
			Push(&parathesisStack, input[i]);
		}
		else if(input[i] == ')')
		{
			temp = Peek(parathesisStack);
			if (temp == '(')
				Pop(&parathesisStack);
			else
				return 0;
		}
	}

	if (isEmpty(parathesisStack))
		return 1;
	return 0;
}

void ParseIntoCommandList(char* inputString)
{
	commandCount = 0;

	char* input = inputString;

	if(!CheckForValidParathesis(inputString))
	{
		// no valid input on the command line
		return;
	}

	int currentPriorityForTheCommand = 0;

	int position = 0;

	while (input[position] != '\n')
	{
		InitializeCommandStruct(commandCount);
		CommandList[commandCount].priority = currentPriorityForTheCommand;
		
		if (input[position] == ' ' || input[position] == '\t')
		{
			while (input[position] == ' ')
			position++;
		}
		
		int cmdPosition = 0;
		while (input[position] != ')' && input[position] != ' ' && input[position] != '\t' && input[position] != ','
				&& input[position] != ';' && input[position] != '|' && input[position] != '&'
				&& input[position] != '\n')
		{
			if (input[position] == '(')
			{
				currentPriorityForTheCommand++;
				CommandList[commandCount].priority = currentPriorityForTheCommand;
			}
			else
			{
				CommandList[commandCount].cmd[cmdPosition] = input[position];
				cmdPosition++;
			}

			position++;
		}
		CommandList[commandCount].cmd[cmdPosition] = '\0';

		if (input[position] == '\n')
		{
			CommandList[commandCount].args = "";
			break;
		}

		if (input[position] == ' ' || input[position] == '\t')
		{
			while (input[position] == ' ')
			position++;
		}

		int argPosition = 0;
		while (input[position] != ',' && input[position] != ';' && input[position] != '|'
				&& input[position] != '&' && input[position] != '\n')
		{
			if (input[position] == ')')
			{
				currentPriorityForTheCommand--;
			}
			else
			{
				CommandList[commandCount].args[argPosition] = input[position];
				argPosition++;
			}
			position++;
		}
		CommandList[commandCount].args[argPosition] = '\0';

		if (input[position] == '\n')
		{
			break;
		}
		
		if (input[position] == ' ' || input[position] == '\t')
		{
			while (input[position] == ' ')
			position++;
		}
			
		CommandList[commandCount].delimiter = input[position];
		commandCount++;
		position++;
	}
	
}

void PrepareArgumentsForCommands()
{
	/*for(int index = 0; index <= commandCount; index++)
	{			
		CommandList[index].argList = (char**)malloc(64 * sizeof(char**));
		CommandList[index].argList[0] = CommandList[index].cmd;
				
		char* argument = strtok(CommandList[index].args, " \t");
		int argIndex = 1;
		while (argument != NULL)
		{
			CommandList[index].argList[argIndex] = argument;
			argIndex++;
			argument = strtok(NULL, " \t");
		}
		CommandList[index].argList[argIndex] = NULL;
	}*/
	
	for(int index = 0; index <= commandCount; index++)
	{
		int argIndex = 0;
		CommandList[index].argList = (char**)malloc(MAX_ARGS * sizeof(char**));
		CommandList[index].argList[argIndex] = (char*) malloc(strlen(CommandList[index].cmd)+1);
		strcpy(CommandList[index].argList[argIndex], CommandList[index].cmd);
		
		char* argument = strtok(CommandList[index].args, " \t\n");
		
		while(argument != NULL)
		{
			argIndex++;
			
			CommandList[index].argList[argIndex] = (char*) malloc(strlen(argument)+1);
			strcpy(CommandList[index].argList[argIndex], argument);
			
			argument = strtok(NULL, " \t\n");	
		}
		
		argIndex++;
		CommandList[index].argList[argIndex] = NULL;
		CommandList[index].argCount = argIndex + 1;
	}
}

void PriotizeCommands()
{
	for (int i = 1; i <= commandCount; i++)
	{
		for (int j = 0; j <= commandCount - i; j++)
		{
			if (CommandList[j].priority < CommandList[j + 1].priority)
			{
				//swap
				int tempPriority = CommandList[j].priority;
				CommandList[j].priority = CommandList[j + 1].priority;
				CommandList[j + 1].priority = tempPriority;

				char tempchar = CommandList[j].delimiter;
				CommandList[j].delimiter = CommandList[j+1].delimiter;
				CommandList[j + 1].delimiter = tempchar;

				char *temp = CommandList[j].args;
				CommandList[j].args = CommandList[j + 1].args;
				CommandList[j + 1].args = temp;

				temp = CommandList[j].cmd;
				CommandList[j].cmd = CommandList[j + 1].cmd;
				CommandList[j + 1].cmd = temp;;

				char** tempList = CommandList[j].argList;
				temp = *(CommandList[j].argList);

				CommandList[j].argList = CommandList[j+1].argList;
				*(CommandList[j].argList) = *(CommandList[j + 1].argList);

				CommandList[j+1].argList = tempList;
				*(CommandList[j+1].argList) = temp;
			}
		}
	}
}

void ParseTheCommand(char* inputString)
{
	ParseIntoCommandList(inputString);	
	PrepareArgumentsForCommands();	
	PriotizeCommands();
}