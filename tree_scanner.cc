#include"header_files/tree_scanner.h"


class FileTreeScanner
{
	private:
		
		string sourceRootDir, destRootDir; // tempPath;
		int logFileFD;
		
		static string THISCLASSNAME;	
		LogWriter objLogWriter;		
		
		//private member functions
		bool CheckSum(const char*,const char*);
		bool IsFileExist(const char*);
		string ParsePath(const char*);

	public:
		//constructor, destructor
		FileTreeScanner(const char*, const char*);
		FileTreeScanner(const char*);
		~FileTreeScanner(){}

		int ScanFiles(string);

};

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
//	tempPath.assign(startRootDir);
	destRootDir.assign(startDestDir);
}

FileTreeScanner::FileTreeScanner(const char* startdir)
{
					
	string THISCLASSNAME = "FileTreeScanner";
	objLogWriter.assignFileName(THISCLASSNAME);	
	
	sourceRootDir.assign(startdir);
//	tempPath.assign(startdir);
}

///////////////////////////////////////////////////
//
//	name:		CheckSum()
//	parameters:	2 const char*
//	return value:	boolean
//	purpose:	check the checksum of source and destination file
//
///////////////////////////////////////////////////

bool FileTreeScanner::CheckSum(const char *sourceFilePath, const char *destinatioFilePath)
{

	//todo add code of checksum of files
	return false;
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
	if(access(FilePath, F_OK) != -1)
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

		if(lstat(tempPath.c_str(),&tempBuffer)<0) //open file or directory inode
		{
			if(errno == ENOENT) //if file of directory does not exist
			{
				objLogWriter.writeToLog("*-Dir Not Found-*"+tempPath);
				break;
			}
			else
			{
				perror("ParsePath: error in File or directory reading");
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
		if( dirEntry -> d_name[0] == '.' && (dirEntry->d_name[1] == '.' || dirEntry ->d_name[1] == '\0'))
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
			//objLogWriter.writeToLog("*-inside dir-* "+tempPath);
			ScanFiles(filepath);
			

		}
		else
		{
			
			//objLogWriter.writeToLog("fullFilePath"+filepath);
			
			destFilePath = filepath;
			destFilePath.replace(0,sourceRootDir.length(),destRootDir.c_str());
			
			DataInPipe objDataInPipe;
			

			if(IsFileExist(destFilePath.c_str()))
			{
				//call for checksum()
				if(!(CheckSum(filepath.c_str(),destFilePath.c_str())))
				{
					objDataInPipe.SourceFilePath = filepath; 
					objDataInPipe.DestFilePath = destFilePath;
					objDataInPipe.existPath = "";
					objDataInPipe.copymode = OVERWRITEFILE;

					//write to pipe
				
				}
				else
				{
					objLogWriter.writeToLog(filepath+": File Not Modified");
				}
			}
			else
			{
				string tempStr = ParsePath(destFilePath.c_str());
				if((tempStr.compare(tempPath.c_str())) == 0)
				{
					objDataInPipe.SourceFilePath = filepath; 
					objDataInPipe.DestFilePath = destFilePath;
					objDataInPipe.existPath = "";
					objDataInPipe.copymode = COPYONLYFILE;

					//write to pipe
				}
				else
				{
					objDataInPipe.SourceFilePath = filepath; 
					objDataInPipe.DestFilePath = destFilePath;
					objDataInPipe.existPath = tempStr;
					objDataInPipe.copymode = COPYWITHDIRSTRUCTURE;

					//write to pipe
				}
					
				cout<<"*-PP Ret Value-*"<<tempStr<<endl;
			}
			
			//code to perform operation on files

			temp_no_of_files++;
		}
		
		filepath = tempPath;

		}

		closedir(dir);
		return 0;
}

/////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{

LogWriter::errorLogInitializer();

FileTreeScanner obj("/home/anuj","/media/anuj/New Volume/Ubuntu_Home_Same");

cout<<"\n__"<<obj.ScanFiles("/home/anuj/");

//cout<<obj.ParsePath("/home/")<<endl;
//cout<<obj.ParsePath("/home/anuj/xyz/abc")<<endl;
//cout<<obj.ParsePath("/home/anuj/Resume/test.bash")<<endl;

printf("\nno of file scanned %d \n",temp_no_of_files);
return 0;
}

/////////////////////////////////////////////////////////////////////