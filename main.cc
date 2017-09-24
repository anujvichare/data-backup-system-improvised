#include"header_files/main.h"
#include<pthread.h>

string source;
string dest;

void* dataCopyThreadFunction(void * params)
{	
//	string &source = *((string*)params[0]);
//	string &dest = *((string*)params[1]);

	DataCopy objDataCopy(source.c_str(), dest.c_str());
	objDataCopy.startDataCopy();
return NULL;
}

void* fileScannerThreadFunction(void * params)
{

//	string &source = *((string*)params[0]);
//	string &dest = *((string*)params[1]);

	FileTreeScanner objFileTreeScanner(source.c_str(),dest.c_str());
	objFileTreeScanner.startScanning();
return NULL;
}


int main(int argc, char *argv[])
{
pthread_t threadId[2];
void* exitStatus[2];

 source="/home/anuj/PROGS/LSP/Marvellous Kernel Module";
 dest ="/media/anuj/New Volume/TestDir";

//string *paths[2];
//paths[0] = &source;
//paths[1] = &dest;

//(void*)paths;

LogWriter::errorLogInitializer();
pthread_create(&threadId[0], NULL, fileScannerThreadFunction, NULL);
pthread_create(&threadId[1], NULL, dataCopyThreadFunction, NULL);

pthread_join(threadId[0], &exitStatus[0]);
pthread_join(threadId[1], &exitStatus[1]);


printf("\nno of file scanned %d \n",temp_no_of_files);

return 0;
}

