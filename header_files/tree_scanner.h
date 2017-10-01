#ifndef TREE_SCANNER_H
#define TREE_SCANNER_H

#include<iostream>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>


#include"log_writer.h"
#include"pipe_requirements.h"

using namespace std;

extern int stat_status;
extern struct stat stat_buf;
extern int temp_no_of_files;

class FileTreeScanner
{
	private:
		
		string sourceRootDir, destRootDir;
		int logFileFD;
		
		static string THISCLASSNAME;	
		LogWriter objLogWriter;		
		
		//private member functions
		bool CheckSum(const char*,const char*);
		bool IsFileExist(const char*);
		string ParsePath(const char*);
		int ScanFiles(string);		
		
//		PIPEFLAGS pipeflag;	
	
		PipeHandler *objPipeHandler;	
	public:
		//constructor, destructor
		FileTreeScanner(const char*, const char*);
		FileTreeScanner(const char*);
		~FileTreeScanner(){}
	
		int startScanning();

};

#endif
