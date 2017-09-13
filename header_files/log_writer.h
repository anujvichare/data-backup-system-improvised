//////////////////////////////////
//
// header file for log writer class
//
/////////////////////////////////

#ifndef LOGWRITER_H
#define LOGWRITER_H

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<iostream>
#include<fcntl.h>

using namespace std;

class LogWriter
{
	
	private: 
		
		static int errorLogFD;
		int activityLogFD;

	public:
		LogWriter();
		~LogWriter();

		int assignFileName(string); 
		int static errorLogInitializer();

		int writeToLog(string);
};

#endif
