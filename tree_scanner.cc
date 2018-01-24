#include"header_files/tree_scanner.h"

/////////////////////////////////////////////////
//
// 	Constructor definations
//
////////////////////////////////////////////////
FileTreeScanner::FileTreeScanner(const char* startRootDir, const char* startDestDir)
{	
	string THISCLASSNAME = "FileTreeScanner";
	objLogWriter.assignFileName(THISCLASSNAME);	
	
	sourceRootDir.assign(startRootDir);
	destRootDir.assign(startDestDir);

	objPipeHandler = new PipeHandler(WRITETOPIPE);//pipeflag.WRITETOPIPE);
}

FileTreeScanner::FileTreeScanner(const char* startdir)
{
					
	string THISCLASSNAME = "FileTreeScanner";
	objLogWriter.assignFileName(THISCLASSNAME);	
	
	sourceRootDir.assign(startdir);

	objPipeHandler = new PipeHandler(WRITETOPIPE);//pipeflag.WRITETOPIPE);

}

///////////////////////////////////////////////////
//
//	name:		CheckSum()
//	parameters:	2 const char*
//	return value:	boolean
//	purpose:	check the checksum of source and destination file
//
///////////////////////////////////////////////////

bool FileTreeScanner::CheckSum(const char *sourceFilePath, const char *destinationFilePath)
{

	//todo add code of checksum of files

	CRC32Calc obj(sourceFilePath, destinationFilePath);

	return obj.calcCheckSum();

//	return false;
}

////////////////////////////////////////////////////
//
// 	name: 		IsFileexist()
//	parameters:	char *
//	return value:	boolean
//	purpose: 	check whether file exist or not
//
///////////////////////////////////////////////////

bool FileTreeScanner::IsFileExist(const char *FilePath)
{
	if(access(FilePath, F_OK) == 0)
	{
		return true;
	}
	
	return false;
}


//////////////////////////////////////////////////////
//
//	name: 		ParsePath()
//	parameters: 	accepts char *
//	returns: 	string object
//	purpose: 	Parse the path till end 
//
/////////////////////////////////////////////////////

string FileTreeScanner::ParsePath(const char *PathToVerify)
{

	string objExistingPath = destRootDir;
	string tempPath = destRootDir;
	struct stat tempBuffer;		

	char *tempStr = new char[strlen(PathToVerify)];
	memcpy(tempStr,PathToVerify,strlen(PathToVerify));
	
	char* tempDirName = strtok((&tempStr[0] + destRootDir.length()),"/");
	
	while(tempDirName != NULL)
	{
		

		tempPath += "/";
		tempPath += tempDirName;

		if(lstat(tempPath.c_str(),&tempBuffer)<0) //open file's or directory's inode
		{
			if(errno == ENOENT) //if file of directory does not exist
			{
			//	objLogWriter.writeToLog("*-Dir Not Found-*"+objExistingPath);
				break;
			}
			else
			{
				perror("ParsePath: error in File or directory reading");
				perror(objExistingPath.c_str());
				return (objExistingPath = "-1");
			}
		}
		else if(S_ISDIR(tempBuffer.st_mode))
		{
			objExistingPath = tempPath;

		}
		else
		{
			objLogWriter.writeToLog("*-Till File-*"+ tempPath);
			break;
		}

		tempDirName = strtok(NULL,"/");
	}
	
	
	delete[](tempStr);
	return objExistingPath;  //returns builded path
}


///////////////////////////////////////////////////
//
//     	name: ScanFiles()	
//	purpose: scan direcory using recurssion
//
///////////////////////////////////////////////////

int FileTreeScanner::ScanFiles(string tempPath)
{
	
	DIR *dir;
	struct dirent *dirEntry;
	string filepath, destFilePath;
	
	filepath = tempPath;	
		
	dir=opendir(tempPath.c_str());
	if(dir==NULL)
	{
		//objLogWriter.writeToLog(tempPath);
		perror("  cant open ");
		perror(tempPath.c_str());
		return 1;
	}

	while((dirEntry = readdir(dir))!= 0 )
	{	
		if( dirEntry -> d_name[0] == '.' ) //&& (dirEntry->d_name[1] == '.'|| dirEntry ->d_name[1] == '\0'))
		{
			//cout<<dirEntry->d_name<<":"<<tempPath<<endl;
			continue;
		}

		filepath += "/";	
		filepath +=  dirEntry->d_name;

		stat_status = lstat(filepath.c_str(),&stat_buf);
		if(stat_status < 0)
		{
				
			perror("  lstat fails ");
			perror(filepath.c_str());
			return 1;
		}

		if(S_ISDIR(stat_buf.st_mode))
		{	
			ScanFiles(filepath); //ecursive call to ScanFile again
			
		}
		else
		{
			
			destFilePath = filepath;
			destFilePath.replace(0,sourceRootDir.length(),destRootDir.c_str());
			
			DataInPipe objDataInPipe;
			

			if(IsFileExist(destFilePath.c_str()))
			{
				
				if(!(CheckSum(filepath.c_str(),destFilePath.c_str())))   //checksum call
				{
					
					strcpy(objDataInPipe.SourceFilePath, filepath.c_str()); 
					strcpy(objDataInPipe.DestFilePath,destFilePath.c_str());
					strcpy(objDataInPipe.existPath, "");
					objDataInPipe.copymode = OVERWRITEFILE;
				
				//	PipeHandler::instance()->writeToPipe(objDataInPipe);//write to pipe
			
					objPipeHandler->writeToPipe(objDataInPipe);//write to pipe
					
					objLogWriter.writeToLog("Overwrite file : "+ filepath);
				
				}
				else
				{
					objLogWriter.writeToLog("File Not Modified : " + filepath);
				}
			}
			else
			{
				string tempStr = ParsePath(destFilePath.c_str()); //Parse Path
				
				string tempDestPath =  tempStr;
				tempDestPath.replace(0,destRootDir.length(),"");
				string tempSourcePath = tempPath;
				tempSourcePath.replace(0,sourceRootDir.length(),"");
				//cout<<tempSourcePath<<" : "<<tempDestPath<<endl;
				
				if((tempDestPath.compare(tempSourcePath.c_str())) == 0)
				{
					strcpy(objDataInPipe.SourceFilePath, filepath.c_str()); 
					strcpy(objDataInPipe.DestFilePath,destFilePath.c_str());
					strcpy(objDataInPipe.existPath,"");
					objDataInPipe.copymode = COPYONLYFILE;
				//	PipeHandler::instance()->writeToPipe(objDataInPipe);//write to pipe

					objPipeHandler->writeToPipe(objDataInPipe);//write to pipe
					
					objLogWriter.writeToLog("Copy Only file: " + filepath);

				}
				else
				{
					strcpy(objDataInPipe.SourceFilePath, filepath.c_str()); 
					strcpy(objDataInPipe.DestFilePath,destFilePath.c_str());
					strcpy(objDataInPipe.existPath,tempStr.c_str());
					objDataInPipe.copymode = COPYWITHDIRSTRUCTURE;
				//	PipeHandler::instance()->writeToPipe(objDataInPipe);//write to pipe

					objPipeHandler->writeToPipe(objDataInPipe);//write to pipe
					
					objLogWriter.writeToLog("Path Exists till dir : " + tempStr);
					objLogWriter.writeToLog("  +------------------- " + filepath);
				}
					
			}
			
			temp_no_of_files++;
		}
		
		filepath = tempPath;

	}
	closedir(dir);
	return 0;
}

int FileTreeScanner::startScanning()
{

	ScanFiles(sourceRootDir);
	
	DataInPipe objDataInPipe;	
	strcpy(objDataInPipe.SourceFilePath,""); 
	strcpy(objDataInPipe.DestFilePath,"");
	strcpy(objDataInPipe.existPath,"");
	objDataInPipe.copymode = SCANCOMPLETE;
	objPipeHandler->writeToPipe(objDataInPipe);
	
	
	return 0;
}




