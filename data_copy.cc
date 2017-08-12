#include"header_files/data_copy.h"


DataCopy::DataCopy(const char* startRootDir, const char* startDestDir)
{
	THISCLASSNAME = "DataCopy";		
	objLogWriter.assignFileName(THISCLASSNAME);
	sourceRootDir.assign(startRootDir);
	destRootDir.assign(startDestDir);
}
DataCopy::~DataCopy()
{}

int DataCopy::createDirStructure()
{
	struct stat statBuf, sourceStatBuf;
	string tempPath = objReadDataFromPipe.existPath;
	string tempSourcePath = tempPath;
	tempSourcePath.replace(0,destRootDir.length(),sourceRootDir.c_str());

	int tempPathLength = tempPath.length();
	
	char *remainingPath = new char[strlen(objReadDataFromPipe.DestFilePath) - tempPathLength];
	
	remainingPath = strtok(&objReadDataFromPipe.DestFilePath[0] + tempPathLength,"/");
	
	while(remainingPath != NULL)
	{		
		tempPath += "/";
		tempSourcePath += "/";
		tempSourcePath += remainingPath;
		tempPath += remainingPath;
		
		if(lstat(tempPath.c_str(), &statBuf) == -1)
		{
			if(lstat(tempSourcePath.c_str(), &sourceStatBuf))
			{
				if(S_ISDIR(sourceStatBuf.st_mode))				
					mkdir(tempPath.c_str(),sourceStatBuf.st_mode); 
			}
		}
		
		remainingPath = strtok(NULL,"/");
		
	}

	delete[](remainingPath);
return 0;	
}

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
                  perror("open :"); 
                  return -1; 
          } 
           
          stat_status=stat(sourceFileName,&statBuf); 
          if(stat_status!=0) 
          { 
                  perror("stat fails : "); 
                  return -1; 
          } 
           
          fdNew=open(destFileName, O_RDWR | O_TRUNC | O_CREAT, statBuf.st_mode); 
          if(fdNew<0) 
          { 
                  perror("newfp open :"); 
                  return -1; 
        } 
           
          while((charsCopied=read(fdOld,buffer,sizeof(buffer)))>0) 
          { 
                 write(fdNew,buffer,charsCopied); 
          } 
  
return 0;
}

int DataCopy::startDataCopy()
{	
	int runFlag = YETTOCOMPLETE;

	
	do
	{
		//read data from pipe
		strcpy(objReadDataFromPipe.SourceFilePath,"/home/anuj/test/test1/test2/abc");
		strcpy(objReadDataFromPipe.DestFilePath,"/media/anuj/New Volume/Ubuntu_Home_Same/test/test1/test2/abc");
		strcpy(objReadDataFromPipe.existPath,"/media/anuj/New Volume/Ubuntu_Home_Same");
		objReadDataFromPipe.copymode = COPYWITHDIRSTRUCTURE;
		
//cout<<objReadDataFromPipe;
	
		switch(objReadDataFromPipe.copymode)
		{
			case COPYWITHDIRSTRUCTURE :
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
							
							break;
			case COPYONLYFILE : 
							if(copyFileData() != 0)	
							{
								objLogWriter.writeToLog("Error : copying data in file");
							}
							break;

			case OVERWRITEFILE :
							if(copyFileData() != 0)	
							{
								objLogWriter.writeToLog("Error : copying data in file");
							}
							break;

			case SCANCOMPLETE :		runFlag = COMPLETE;
							break;
		}
			
		strcpy(objReadDataFromPipe.SourceFilePath,"/home/anuj/test/test1/test2/abc");
		strcpy(objReadDataFromPipe.DestFilePath,"/media/anuj/New Volume/Ubuntu_Home_Same/test/test1/test2/abc");
		strcpy(objReadDataFromPipe.existPath,"/media/anuj/New Volume/Ubuntu_Home_Same");
		objReadDataFromPipe.copymode = SCANCOMPLETE;		
	}while(runFlag != COMPLETE);
	
	return 0;	
}




int main()
{
DataCopy obj("/home/anuj","/media/anuj/New Volume/Ubuntu_Home_Same");

obj.startDataCopy();

return 0;
}