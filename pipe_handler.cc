#include"header_files/pipe_requirements.h"


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
}

PipeHandler *PipeHandler::pipeHandler;
PipeHandler* PipeHandler::instance()
{
	if(!pipeHandler)
		pipeHandler = new PipeHandler();
	
	return pipeHandler;
}

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
	else{cout<<errno<<endl;}	

	return readChars;
}

int PipeHandler::writeToPipe(DataInPipe &data)
{
	int writtenChars = write(writerDescriptor, &data, PIPEDATASIZE);
/*	
	cout<<"-----------------------------------------"<<endl;

	cout<<data.copymode<<endl;
	cout<<data.SourceFilePath<<endl;
	cout<<data.DestFilePath<<endl;
	cout<<data.existPath<<endl;

	cout<<"========================================="<<endl;
*/	
	return writtenChars;
}













