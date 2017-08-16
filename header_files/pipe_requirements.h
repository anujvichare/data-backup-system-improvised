
/////////////////////////////////////////////
//
//  Header file for Pipe class requirements
//	
//
////////////////////////////////////////////

#ifndef PIPEREQUIREMENTS_H
#define PIPEREQUIREMENTS_H

//required header files
#include<string.h>
#include<unistd.h>

//FLAGS
#define COPYONLYFILE 1
#define COPYWITHDIRSTRUCTURE 2
#define OVERWRITEFILE 3
#define SCANCOMPLETE 0

//structure to write and read data from file
typedef struct DataInPipe
{
	char SourceFilePath[500];
	char DestFilePath[500];
	char existPath[500];
	int copymode;
} DataInPipe;

#define PIPEDATASIZE sizeof(DataInPipe)

#endif

