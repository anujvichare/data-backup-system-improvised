///////////////////////////////////////////////////////////////
//
//  this file contains function definations of data copy class 
//
///////////////////////////////////////////////////////////////


#include"header_files/data_copy.h"
#include<errno.h>

///////////////////////////////////////////////////
//
//   	Constructor definations
//
////////////////////////////////////////////////////
DataCopy::DataCopy(const char* startRootDir, const char* startDestDir)
{
	THISCLASSNAME = "DataCopy";		
	objLogWriter.assignFileName(THISCLASSNAME);
	sourceRootDir.assign(startRootDir);
	destRootDir.assign(startDestDir);

	
	objPipeHandler = new PipeHandler(READFROMPIPE);	
}
DataCopy::~DataCopy()
{}

/////////////////////////////////////////////////////
//
// 	name:		createDirStructure()
//	parameters: 	null
//	return value:	int (0 if success / -1 if fails)
//	purpose: 	create missing directry structure to copy or overwrite a file.
//
/////////////////////////////////////////////////////

int DataCopy::createDirStructure()
{
	struct stat statBuf, sourceStatBuf;
	DataInPipe tempObj = objReadDataFromPipe;
	string tempPath = objReadDataFromPipe.existPath;
	string tempSourcePath = tempPath;
	tempSourcePath.replace(0,destRootDir.length(),sourceRootDir.c_str());
	
	int tempPathLength = tempPath.length();
	
	char *remainingPath = new char[strlen(tempObj.DestFilePath) - tempPathLength];
	
	remainingPath = strtok(&tempObj.DestFilePath[0] + tempPathLength,"/");
	
	while(remainingPath != NULL)
	{		
		tempPath += "/";
		tempSourcePath += "/";
		tempSourcePath += remainingPath;
		tempPath += remainingPath;
		
			
		int status = lstat(tempPath.c_str(), &statBuf); 		
		if((status == -1 && errno == ENOENT)  || !(S_ISDIR(statBuf.st_mode)))
		{
				
				if(lstat(tempSourcePath.c_str(), &sourceStatBuf) == 0)
				{
					if(S_ISDIR(sourceStatBuf.st_mode))				
					{
						if(mkdir(tempPath.c_str(),0777) != 0) //sourceStatBuf.st_mode); 
						{
							cout<<errno;
							perror("_DC_ Cannot create directory: ");
							return -1;
						}
					}
				}
			
		}
		
		remainingPath = strtok(NULL,"/");
		
	}

	delete[](remainingPath);
return 0;	
}


/////////////////////////////////////////////////////////
//
//	name:		copyFileData()
//	parameters:	null
//	return value:	int (0 if success / -1 if fails)
//	purpose:	copies data in file to destination
//
//////////////////////////////////////////////////////////
int DataCopy::copyFileData()
{
	char *sourceFileName = objReadDataFromPipe.SourceFilePath;
	char *destFileName = objReadDataFromPipe.DestFilePath; 
  	int fdOld, fdNew, stat_status, charsCopied; 
        struct stat statBuf; 
        char buffer[256]; 
           
         fdOld=open(sourceFileName,O_RDONLY); 
          if(fdOld<0) 
          { 
                  perror("_DC_ open :"); 
                  return -1; 
          } 
           
          stat_status=stat(sourceFileName,&statBuf); 
          if(stat_status!=0) 
          { 
                  perror("_DC_ stat fails : "); 
                  return -1; 
          } 
           
          fdNew=open(destFileName, O_RDWR | O_TRUNC | O_CREAT, statBuf.st_mode); 
          if(fdNew<0) 
          { 
		
                  perror("_DC_ newfp open :"); 
		  write(2,destFileName,100);
                  return -1; 
          } 
           
          while((charsCopied=read(fdOld,buffer,sizeof(buffer)))>0) 
          { 
                 write(fdNew,buffer,charsCopied); 
          } 
  
	
	close(fdNew);
	close(fdOld);
return 0;
}

/////////////////////////////////////////////////////////
//
//	name:		startDataCopy()
//	parameters:	null
//	return value:	int (0 if success / -1 if fails)
//	purpose:	start copying data read from pipe 
//
//////////////////////////////////////////////////////////

int DataCopy::startDataCopy()
{	
	int runFlag = YETTOCOMPLETE;

	
	do
	{
		objReadDataFromPipe = EmptyStruct;
		//int charsRead = PipeHandler::instance()->readFromPipe(objReadDataFromPipe);
	
		int charsRead = objPipeHandler->readFromPipe(objReadDataFromPipe);
		if(charsRead == -1)
		{
			usleep(10000);
			continue;
		}

		switch(objReadDataFromPipe.copymode)
		{
			case COPYWITHDIRSTRUCTURE : // cout<<"COPYWITHDIRSTRUCTURE"<<endl;
							if(createDirStructure() == 0)
							{
								if(copyFileData() != 0)
								{
									objLogWriter.writeToLog("Error: 1 copying data in file");
								}
							}
							else
							{
								objLogWriter.writeToLog("Error: creating dir structure");
							}
							
								objLogWriter.writeToLog("Copy with dir structure : "+ (string)objReadDataFromPipe.SourceFilePath);
							break;
			case COPYONLYFILE : // cout<<"COPYONLYFILE"<<endl;
 
							if(copyFileData() != 0)	
							{
								objLogWriter.writeToLog("Error : copying data in file");
							}

								objLogWriter.writeToLog("Copy only file : "+ (string)objReadDataFromPipe.SourceFilePath);
							break;

			case OVERWRITEFILE :// cout<<"OVERWITEFILE"<<endl;

							if(copyFileData() != 0)	
							{
								objLogWriter.writeToLog("Error : copying data in file");
							}

								objLogWriter.writeToLog("Overwrite file : "+ (string)objReadDataFromPipe.SourceFilePath);
							break;

			case SCANCOMPLETE : // cout<<"SCANCOMPLETE"<<endl;

						runFlag = COMPLETE;
							break;
		}
			
	}while(runFlag != COMPLETE);
	
	return 0;	
}




