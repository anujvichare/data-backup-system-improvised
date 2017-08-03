#include"header_files/tree_scanner.h"


class FileTreeScanner
{
	private:
		
		string sourceRootDir, destRootDir, tempPath;
		int logFileFD;
		
		static string THISCLASSNAME;	
		LogWriter objLogWriter;		
		
		//private member functions
		bool CheckSum(const char*,const char*);
		bool IsFileExist(const char*);
		string ParsePath(const char*);

	public:
		//constructor
		FileTreeScanner(const char* startRootDir, const char* startDestDir)
		{	
			string THISCLASSNAME = "FileTreeScanner";
			objLogWriter.assignFileName(THISCLASSNAME);	
	
			sourceRootDir.assign(startRootDir);
			tempPath.assign(startRootDir);
	
			destRootDir.assign(startDestDir);
		}
		FileTreeScanner(const char* startdir)
		{
					
			string THISCLASSNAME = "FileTreeScanner";
			objLogWriter.assignFileName(THISCLASSNAME);	
	
			sourceRootDir.assign(startdir);
			tempPath.assign(startdir);
		}
		
		//destructor
		~FileTreeScanner(){}

		int ScanFiles(string);

};

bool FileTreeScanner::CheckSum(const char *sourceFilePath, const char *destinatioFilePath)
{

	return true;
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
//	char *PathToVerify = PathToVerify_const;
	string objExistingPath = destRootDir;
	string tempPath = destRootDir;
	struct stat tempBuffer;		

	char * tempStr;
	strcpy(tempStr,PathToVerify);

	char* tempDirName = strtok((&tempStr[0] + objExistingPath.length()),"/");
	
	while(tempDirName != NULL)
	{
		tempPath += "/";
		tempPath += tempDirName;

		if(lstat(tempPath.c_str(),&tempBuffer)<0)
		{
			if(errno == ENOENT)
				break;
		}
		else if(S_ISDIR(tempBuffer.st_mode))
		{
			objExistingPath += tempPath;
		}
		else
		{
			break;
		}

		tempDirName = strtok(NULL,"/");
	}
	
	

	return objExistingPath;
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
		if( dirEntry -> d_name[0] == '.')
		{
			//strcpy(filepath,tempPath);
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
			objLogWriter.writeToLog("--inside dir "+tempPath);
			ScanFiles(filepath);
			

		}
		else
		{
			
			objLogWriter.writeToLog(filepath);
			
			destFilePath = filepath;
			destFilePath.replace(0,sourceRootDir.length(),destRootDir.c_str());
			
			if(IsFileExist(destFilePath.c_str()))
			{
				//call for checksum
			}
			else
			{
				string tempStr = ParsePath(destFilePath.c_str());
			//ToDO	
				cout<<tempStr<<endl;
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

FileTreeScanner obj("/home/anuj","/home/anuj");

cout<<"\n__"<<obj.ScanFiles("/home/anuj");

printf("\nno of file scanned %d \n",temp_no_of_files);
return 0;
}

//////////////////////////////////////////////////////////////////
