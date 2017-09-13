///////////////////////////////////////////////
//
// 	file contains all function defination for log writing
//
//////////////////////////////////////////////

#include"header_files/log_writer.h"

// constructor
	LogWriter::LogWriter()
	{
	}
	

/////////////////////////////////////////////////////////
//
//	name:		assignFileName()
//	parameters:	std::string
//	return value:	int (0 if success / -1 if fails)
//	purpose:	assign filename to logfile generated by each class
//
//////////////////////////////////////////////////////////
	
	int LogWriter::assignFileName(string LogFileName)
	{
			
		if((activityLogFD = open((LogFileName+"_activity.log").c_str(),O_RDWR|O_CREAT,0666))<0)
		{
				perror("unable to open activityLogFile");
				return -1;
		}
		return 0;
	}

//destructor		
	LogWriter::~LogWriter()
	{
	}

/////////////////////////////////////////////////////////
//
//	name:		writeToLog()
//	parameters:	std::string
//	return value:	int (0 if success / -1 if fails)
//	purpose:	writes a log to associated file
//
//////////////////////////////////////////////////////////
	
	int LogWriter::writeToLog(string statement)
		{	
			int statementLength;
			statement += "\n";
			
			statementLength = statement.length();

			write(activityLogFD,statement.c_str(),statementLength);
			return 0;
		}

/////////////////////////////////////////////////////////
//
//	name:		errorLogInitializer() "static"
//	parameters:	null
//	return value:	int (0 if success / -1 if fails)
//	purpose:	redirects stderr to 'Errors.log' file 
//
//////////////////////////////////////////////////////////

	int LogWriter::errorLogFD;
	int  LogWriter::errorLogInitializer()
	{
			if((errorLogFD = open("Errors.log",O_RDWR|O_CREAT,0666))<0)
			{
				perror("Unable to create Error.log");
				
				return -1;
			}
			close(2);
			dup(errorLogFD);
		
			return 0;
	}
