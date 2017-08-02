
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
#define COPYFILEONLY 1
#define COPYWITHDIRSTRUCTURE 2


//structure to write and read data from file
typedef struct DataInPipe
{
	string SourcePath;
	string DestPath;
	string existpath;
	int copymode;
} DataInPipe;



