#include"header_files/main.h"


int main(int argc, char *argv[])
{
string source="/home/anuj/PROGS/LSP/Marvellous Kernel Module";
string dest ="/media/anuj/New Volume/TestDir";

LogWriter::errorLogInitializer();

FileTreeScanner obj(source.c_str(),dest.c_str());
DataCopy objDataCopy(source.c_str(), dest.c_str());

cout<<"\n__"<<obj.startScanning();
printf("\nno of file scanned %d \n",temp_no_of_files);

objDataCopy.startDataCopy();

return 0;
}

