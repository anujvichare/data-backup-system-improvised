///////////////////////////////////////////////////////////
//
//	file contains functions for Named pipe handeling
//
///////////////////////////////////////////////////////////

#include"header_files/pipe_requirements.h"

///////////////////////////////////////////////////////////
//
// 	constructors and destructors
//
//////////////////////////////////////////////////////////
PipeHandler::PipeHandler()
{

}
PipeHandler::PipeHandler(int task)
{
	
	readerDescriptor = 0;
	writerDescriptor = 0;
	
	objLogWriter.assignFileName("PipeHandler");
	int retValue;
	
	string fifo = "/tmp/data_backup_system_pipe"; 
	
	switch(task)	
	{	
	
	case CREATEPIPE :

			int status;
			status = mkfifo(fifo.c_str(),0666);
			if(status < 0)
			{
				perror("unable to create FIFO");
				cout<<errno;
				exit(0);
				
			}

			objLogWriter.writeToLog("Pipe Created successfully");
			break;

	case READFROMPIPE :

			readerDescriptor = open(fifo.c_str(), O_RDONLY);
			if(readerDescriptor < 0)
			{
				perror("cant open fifo to read");
			
			}
			break;
			
	case WRITETOPIPE :
		
			writerDescriptor = open(fifo.c_str(), O_WRONLY);
			if(writerDescriptor < 0)
			{
				perror("cant open fifo to write");
			}
			break;

	default :
			break;
	};	

		
}

PipeHandler::~PipeHandler()
{
	if(readerDescriptor > 2)
		 close(readerDescriptor);
	
	if(writerDescriptor > 2)  
		 close(writerDescriptor);
	
	unlink("/tmp/data_backup_system_pipe");

	objLogWriter.writeToLog("pipe closed");

	objLogWriter.~LogWriter();
}


/////////////////////////////////////////////////////////
//
//	name:		readFromPipe()
//	parameters:	null
//	return value:	int (read character count if success / return value of read())
//	purpose:	read data chunk from pipe
//
//////////////////////////////////////////////////////////

int PipeHandler::readFromPipe(DataInPipe &data)
{
	char Buffer[PIPEDATASIZE];
	int readChars = read(readerDescriptor, Buffer, PIPEDATASIZE);
	
	if(readChars > 0)
	{	
		strcpy(data.SourceFilePath, Buffer+1);
		strcpy(data.DestFilePath, Buffer+501);
		strcpy(data.existPath, Buffer+1001);
		
		/*memcpy(data.SourceFilePath, Buffer+1, 500);
		memcpy(data.DestFilePath, Buffer+501, 500);
		memcpy(data.existPath, Buffer+1001, 500);*/
		data.copymode = Buffer[0];

/*	cout<<"-----------------------------------------"<<endl;

	cout<<data.copymode<<endl;
	cout<<data.SourceFilePath<<endl;
	cout<<data.DestFilePath<<endl;
	cout<<data.existPath<<endl;

	cout<<"========================================="<<endl;
*/		
	}
	else{
		
		objLogWriter.writeToLog("error occured in pipe reading with error: "+ std::to_string(errno));
		cout<<"reading :"<<errno<<endl;
		}	

	return readChars;
}

/////////////////////////////////////////////////////////
//
//	name:		writeToPipe()
//	parameters:	DataInPipe &
//	return value:	int (return value of write())
//	purpose:	write data chunk to file
//
//////////////////////////////////////////////////////////

int PipeHandler::writeToPipe(DataInPipe &data)
{
	int writtenChars = write(writerDescriptor, &data, PIPEDATASIZE);
	if(writtenChars > 0)	
	{
		/*	

		cout<<"-----------------------------------------"<<endl;

		cout<<data.copymode<<endl;
		cout<<data.SourceFilePath<<endl;
		cout<<data.DestFilePath<<endl;
		cout<<data.existPath<<endl;

		cout<<"========================================="<<endl;
		*/	
	}
	if(writtenChars == 0)
	{

		objLogWriter.writeToLog("did not write in pipe");

			//objLogWriter.writeToLog(data.copymode);
			objLogWriter.writeToLog(data.SourceFilePath);
			objLogWriter.writeToLog(data.DestFilePath);
			objLogWriter.writeToLog(data.existPath);


		objLogWriter.writeToLog("----------------");
		
	}
	else if(writtenChars < 0)
	{

		objLogWriter.writeToLog("error occured while writing in pipe: "+ std::to_string(errno) );
		cout<<"writing :"<<errno<<endl;
	}		
	
	objLogWriter.writeToLog("writtenChars"+ std::to_string(writtenChars));
	return writtenChars;
}













