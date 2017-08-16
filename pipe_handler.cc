#include"header_files/pipe_requirements.h"

class PipeHandler
{

	private:
		int readerDescriptor, writerDescriptor;
		PipeHandler *pipeHandler;

		PipeHandler();
	public:
		~PipeHandler();
		PipeHandler* instance();
		int writeToPipe();
		int readFromPipe();
		
};


PipeHandler::PipeHandler()
{
	int retValue;
	int fd[2];
	
	if((retValue = pipe(fd) < 0)
	{
		
		perror("Unable to create Pipe: existing...");
		exit(0);
	}

	readerDescriptor = fd[0];
	writerDescriptor = fd[1];

}

PipeHandler::~PipeHandler()
{
	close(readerDescriptor);
	close(writerDescriptor);
}

PipeHandler* PipeHandler::instance()
{
	if(!pipeHandler)
		pipeHandler = new Pipehandler();
	
	return pipeHandler
}

int readFromPipe(DataInPipe &data)
{
	char Buffer[sizeof(DataInPipe)];
	
}




















