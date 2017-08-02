#include"header_files/tree_scanner.h"


class FileTreeScanner
{
	private:
		
		string SourceRootDir, DestRootDir, tempPath;
		int LogFileFD;
		
		static string ThisClassName;	
		LogWriter objLogWriter;		
		
		//private member functions
		bool Checksum(const char*,const char*);
		bool isFileExist(const char*);
		string ParsePath(const char*);

	public:
		//constructor
		FileTreeScanner(const char*, const char*)
		{
			
		}
		FileTreeScanner(const char* startdir)
		{	
				
			string ThisClassName = "FileTreeScanner";
			objLogWriter.assignFileName(ThisClassName);	
	
			SourceRootDir.assign(startdir);
			tempPath.assign(startdir);
		}
		
		//destructor
		~FileTreeScanner(){}

		int ScanFiles(string);

};

bool FileTreeScanner::Checksum(const char *sourceFilePath, const char *destinatioFilePath)
{

	return true;
}

bool FileTreeScanner::isFileExist(const char *FilePath)
{
	if(access(FilePath, F_OK) != -1)
	{
		return true;
	}
	
	return false;
}

string FileTreeScanner::ParsePath(const char *PathRootDir)
{
	string objExistingPath;


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
	string filepath;
	
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
			objLogWriter.writeToLog(tempPath);
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

FileTreeScanner obj("/home/anuj");

cout<<"\n__"<<obj.ScanFiles("/home/anuj");

printf("\nno of file scanned %d \n",temp_no_of_files);
return 0;
}

//////////////////////////////////////////////////////////////////
