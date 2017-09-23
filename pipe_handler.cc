///////////////////////////////////////////////////////////
//
//	file contains functions for pipe handeling
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
	int retValue;
	int fd[2];
	
	if((retValue = pipe2(fd, O_NONBLOCK)) < 0)
	{
		
		perror("Unable to create Pipe: exiting...");
		exit(0);
	}	
	
	objLogWriter.assignFileName("PipeHandler");
	readerDescriptor = fd[0];
	writerDescriptor = fd[1];
	
	objLogWriter.writeToLog("Pipe Created successfully");

}

PipeHandler::~PipeHandler()
{
	close(readerDescriptor);
	close(writerDescriptor);
	objLogWriter.writeToLog("pipe closed");
}

/////////////////////////////////////////////////////////
//
//	name:		instance()
//	parameters:	null
//	return value:	Pipehandler*
//	purpose:	factory method to return instance of a singleton class
//
//////////////////////////////////////////////////////////

PipeHandler *PipeHandler::pipeHandler;
PipeHandler* PipeHandler::instance()
{
	if(!pipeHandler)
	{
		pipeHandler = new PipeHandler();
		cout<<"pipe initialization..";
	}
	return pipeHandler;
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













