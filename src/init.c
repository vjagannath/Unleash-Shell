#include "init.h"

extern char **aliasList;
extern int aliasListSize;

void SetLocalEnvVar(char *line)
{
	char *vari = NULL;
	char *value = NULL;
	vari = strtok(line, "=");
	if(vari != NULL)
	{
		//printf("%s : ", vari);
		value = strtok(NULL, "\r\n");
		if(value != NULL)
		{
			//printf("%s\n", value);
			setenv(vari, value, 1);
		}
	}
}

int ReadProfile(char *progPath)
{
	FILE *fp = NULL;
	char *line = NULL;
    size_t len = 0;
    ssize_t read;
	int retStatus = 0;
	char *progName = strrchr(progPath, '/');  
	
	strncpy(profilePath, progPath, (progName - progPath + 1));
	
	strcat(profilePath, profileFileName);
	//printf("Profile File :  %s", profilePath);
	
	fp = fopen(profilePath, "r");
	if (fp != NULL)
	{
		while ((read = getline(&line, &len, fp)) != -1) 
		{
			//printf("Retrieved line of length %zu :\n", read);
			//printf("%s\n", line);
			SetLocalEnvVar(line);
		}
		
		fclose(fp);
		if (line)
			free(line);
	}
	else
	{
		perror("Error reading profile file");
		retStatus = -1;
	}
	
	return retStatus;
}

int ReadAlias(char *progPath)
{
	FILE *fp = NULL;
	char *line = NULL;
    size_t len = 0;
    ssize_t read;
	int retStatus = 0;
	char *progName = strrchr(progPath, '/');
	char *aliasEntry=NULL;
	
	aliasListSize = 0;
	aliasList = (char**)malloc(MAX_ALIAS_LIST_SIZE * sizeof(char*));
	memset(aliasList, 0, MAX_ALIAS_LIST_SIZE * sizeof(char*));
	
	strncpy(aliasPath, progPath, (progName - progPath + 1));
	
	strcat(aliasPath, aliasFileName);
	//printf("Profile File :  %s", profilePath);
	
	fp = fopen(aliasPath, "r");
	if (fp != NULL)
	{
		while ((read = getline(&line, &len, fp)) != -1) 
		{
			aliasEntry = strtok(line, "\r\n");
			
			aliasList[aliasListSize] = (char *)malloc(strlen(aliasEntry) + 1);
			strcpy(aliasList[aliasListSize], aliasEntry);
			aliasListSize++;	
		}
		
		fclose(fp);
		if (line)
			free(line);
	}
	else
	{
		perror("Error reading alias file");
		retStatus = -1;
	}
	
	return retStatus;
}

void DumpAliasList()
{
	int i;
	if (truncate(aliasPath, 0) != -1)
	{
		FILE *fp = fopen(aliasPath,"w");
		if(fp != NULL)
		{
			//printf("AliasListSize %d\n", aliasListSize);
			
			for(i = 0; i < aliasListSize; i++)
			{
				fprintf(fp,"%s\n",aliasList[i]);
				
				//printf("Item %d = %s\n", i, aliasList[i]);
			}
			
			fclose(fp);
		}
		else
		{
			perror("Could not open alias file for writing");
		}
    }
	else
	{
		perror("Could not clear contents of alias file");
	}
}

int InitializeShellEnvironment(char *progPath)
{
	int retStatus = 0;
	
	retStatus = ReadProfile(progPath);
	
	if(retStatus == 0)
	{
		//printf("$HOME : %s\n", getenv("HOME"));
		
		if(chdir(getenv("HOME")) != 0)
		{
			retStatus = -1;
			perror("$HOME is invalid");
		}
		
	}
	
	retStatus = ReadAlias(progPath);
	
	return retStatus;
}

