
/////////////////////////////////////////////
//
//  Header file for Pipe class requierments
//	
//
////////////////////////////////////////////

#ifndef PIPEREQUIREMENT_H
#define PIPEREQUIREMENT_H

//required header files
#include<string.h>

//FLAGS
#define COPYONLYFILE 1
#define COPYWITHDIRSTRUCTURE 2
#define OVERWRITEFILE 3

//structure to write and read data from file
typedef struct DataInPipe
{
	string SourceFilePath;
	string DestFilePath;
	string existPath;
	int copymode;
} DataInPipe;

#endif

