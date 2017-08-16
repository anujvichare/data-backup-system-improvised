#include"header_files/data_copy.h"
#include<errno.h>


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
		if((status == -1 && errno == EIO)  || !(S_ISDIR(statBuf.st_mode)))
		{
				
				if(lstat(tempSourcePath.c_str(), &sourceStatBuf) == 0)
				{
					if(S_ISDIR(sourceStatBuf.st_mode))				
					{
						if(mkdir(tempPath.c_str(),0777) != 0) //sourceStatBuf.st_mode); 
						{
							cout<<errno;
							perror("Cannot create directory: ");
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

	
//	do
//	{
		//read data from pipe
		strcpy(objReadDataFromPipe.SourceFilePath,"/home/anuj/test/test1/test2/abc");
		strcpy(objReadDataFromPipe.DestFilePath,"/media/anuj/New Volume/Ubuntu_Home_Same/test/test1/test2/abc");
		strcpy(objReadDataFromPipe.existPath,"/media/anuj/New Volume/Ubuntu_Home_Same");
		objReadDataFromPipe.copymode = SCANCOMPLETE;//OVERWRITEFILE;//COPYONLYFILE; //COPYWITHDIRSTRUCTURE;
		

	
		switch(objReadDataFromPipe.copymode)
		{
			case COPYWITHDIRSTRUCTURE : cout<<"COPYWITHDIRSTRUCTURE";
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
			case COPYONLYFILE : cout<<"COPYONLYFILE";
 
							if(copyFileData() != 0)	
							{
								objLogWriter.writeToLog("Error : copying data in file");
							}
							break;

			case OVERWRITEFILE : cout<<"OVERWITEFILE";

							if(copyFileData() != 0)	
							{
								objLogWriter.writeToLog("Error : copying data in file");
							}
							break;

			case SCANCOMPLETE :  cout<<"SCANCOMPLETE";

						runFlag = COMPLETE;
							break;
		}
			
//}while(runFlag != COMPLETE);
	
	return 0;	
}




int main()
{
DataCopy obj("/home/anuj","/media/anuj/New Volume/Ubuntu_Home_Same");

obj.startDataCopy();

return 0;
}
