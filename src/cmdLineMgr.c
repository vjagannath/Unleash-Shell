#include "commonIncludes.h"

jmp_buf jumpLoc;

void SetPrompt()
{
	char directoryPath[PATH_MAX] = {'\0'};
	char *prompt = NULL;	
	char delimiter = '/';
	char *directoryName = NULL;
	
	getcwd(directoryPath, sizeof(directoryPath));
	
	//directoryPath = getenv("PWD");
	prompt = getenv("PROMPT");
	
	directoryName = strrchr(directoryPath, delimiter);
	
	//printf("Here\n");
	if(directoryName != NULL)
	{
		directoryName++;	
		printf("\n(%s)%s ", directoryName, prompt);
	}
}

void AbortHandler(int param)
{
	char confirmation[4];  
	printf("\nAre you sure?[y/N]: ");
	scanf("%3s", confirmation);

	if(	(strcmp(confirmation, "y") == 0)|| 
		(strcmp(confirmation, "Y") == 0)|| 
		(strcmp(confirmation, "yes") == 0)|| 
		(strcmp(confirmation, "YES") == 0))
	{
		DumpAliasList();
		exit(0);
	}
	else
		longjmp(jumpLoc,1);
}

void ReadCmd(char ** cmdLine)
{
    size_t len = 0;
    ssize_t read;
	
	signal(SIGINT, AbortHandler);  	
	setjmp(jumpLoc);
  
	read = getline(cmdLine, &len, stdin);
}