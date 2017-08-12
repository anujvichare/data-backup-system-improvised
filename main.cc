#include"header_files/main.h"


int main(int argc, char *argv[])
{

LogWriter::errorLogInitializer();

FileTreeScanner obj("/home/anuj","/media/anuj/New Volume/Ubuntu_Home_Same");

cout<<"\n__"<<obj.startScanning();

//cout<<obj.ParsePath("/home/")<<endl;
//cout<<obj.ParsePath("/home/anuj/xyz/abc")<<endl;
//cout<<obj.ParsePath("/home/anuj/Resume/test.bash")<<endl;

printf("\nno of file scanned %d \n",temp_no_of_files);
return 0;
}

/////////////////////////////////////////////////////////////////////
