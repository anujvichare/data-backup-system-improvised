///////////////////////////////////////
//
//  header file for data copy class
//
//////////////////////////////////////

#ifndef DATA_COPY_H
#define DATA_COPY_H

#include<iostream>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>


#include"log_writer.h"
#include"pipe_requirements.h"

using namespace std;


#define COMPLETE 0
#define YETTOCOMPLETE 1

//class defination
class DataCopy
{

	private:
		string sourceRootDir, destRootDir;		
		
		string THISCLASSNAME;
		DataInPipe objReadDataFromPipe;
		LogWriter objLogWriter;

		int createDirStructure();
		int copyFileData();
		
		PipeHandler *objPipeHandler;	
	public:
		DataCopy(const char*, const char*);
		~DataCopy();
		int startDataCopy();
		

};

#endif
