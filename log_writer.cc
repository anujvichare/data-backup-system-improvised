#include"header_files/log_writer.h"


	LogWriter::LogWriter()
	{
	}
			
	int LogWriter::assignFileName(string LogFileName)
	{
			
		if((activityLogFD = open((LogFileName+"_activity.log").c_str(),O_RDWR|O_CREAT,0666))<0)
		{
				perror("unable to open activityLogFile");
				return -1;
		}
		return 0;
	}
		
	LogWriter::~LogWriter()
	{
	}

		
	int LogWriter::writeToLog(string statement)
		{	
			int statementLength;
			statement += "\n";
			
			statementLength = statement.length();

			write(activityLogFD,statement.c_str(),statementLength);
			return 0;
		}


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
