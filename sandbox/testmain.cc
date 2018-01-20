
#include"header_files/crc32_calculator.h"
#include<iostream>

int main()
{

CRC32Calc obj("../abc.txt", "./abc.txt");

cout<<obj.calcCheckSum();

return 0;
}

/*

DataInPipe obj[5];

strcpy(obj[0].SourceFilePath,"objonesourcefilepath");
strcpy(obj[0].DestFilePath,"objoneDestfilepath");
strcpy(obj[0].existPath,"objoneExistpath");
obj[0].copymode = 1;

 PipeHandler::instance()->readFromPipe(obj[4]);

strcpy(obj[1].SourceFilePath,"objTwosourcefilepath");
strcpy(obj[1].DestFilePath,"objTwoDestfilepath");
strcpy(obj[1].existPath,"objTwoExistpath");
obj[1].copymode = 2;

int w1  = PipeHandler::instance()->writeToPipe(obj[0]);
int w2 = PipeHandler::instance()->writeToPipe(obj[1]);

int r1= PipeHandler::instance()->readFromPipe(obj[2]);
int r2 = PipeHandler::instance()->readFromPipe(obj[3]);
int r3 =  PipeHandler::instance()->readFromPipe(obj[4]);
cout<<w1<<","<<w2<<"::"<<r1<<","<<r2<<","<<r3 ;


*/

/*
 int main()
 {
 DataCopy obj("/home/anuj","/media/anuj/New Volume/Ubuntu_Home_Same");
 
 obj.startDataCopy();
 
 return 0;
 }
*/


