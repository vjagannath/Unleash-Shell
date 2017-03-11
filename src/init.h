#ifndef INIT_H_
#define INIT_H_

//Includes
#include "commonIncludes.h"

//Defines
#define MAX_ALIAS_LIST_SIZE 512

//Global Variables
static const char profileFileName[] = ".profile";
static const char aliasFileName[] = ".alias";
static char profilePath[PATH_MAX] = {'\0'};
static char aliasPath[PATH_MAX] = {'\0'};

//Type Definitions
 

//Function Declarations
void SetLocalEnvVar(char *line);
int ReadProfile(char *progPath);


#endif //INIT_H_

