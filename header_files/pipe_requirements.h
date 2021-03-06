
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
#include<stdlib.h>
#include<errno.h>
#include<sys/stat.h>
#include"log_writer.h"




//FLAGS
#define COPYONLYFILE 1
#define COPYWITHDIRSTRUCTURE 2
#define OVERWRITEFILE 3
#define SCANCOMPLETE 0
#define CREATEPIPE 10
#define READFROMPIPE 11
#define WRITETOPIPE 12

/*
typedef enum
{  = 10,
 READFROMPIPE = 11,
 WRITETOPIPE = 12
} PIPEFLAGS;

PIPEFLAGS pipeFlags;
*/

//structure to write and read data from file
typedef struct DataInPipe
{
	char copymode;
	char SourceFilePath[500];
	char DestFilePath[500];
	char existPath[500];
	
} DataInPipe;

#define PIPEDATASIZE sizeof(DataInPipe)

static const DataInPipe EmptyStruct = {0,"/0","/0","/0"};
 
 class PipeHandler
 {
   
	private:
	  int readerDescriptor, writerDescriptor;
	  LogWriter objLogWriter; 	
//	  static PipeHandler *pipeHandler;
	
	public:
	  PipeHandler(int);
	  PipeHandler();
	  ~PipeHandler();

	  int writeToPipe(DataInPipe &);
	  int readFromPipe(DataInPipe &);

 };



#endif

