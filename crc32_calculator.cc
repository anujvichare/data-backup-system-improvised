/* Crc - 32 BIT ANSI X3.66 CRC checksum files */

#include "header_files/crc32_calculator.h"
struct temp 
{
CRC32Calc* thisPtr;
int flag;
};

// constructor

CRC32Calc::CRC32Calc()
{

}

CRC32Calc::CRC32Calc(string sourceFile, string destFile)
{
	sourceFilePath = sourceFile;
	destFilePath = destFile;

	sourceCheckSum = 0;
	destCheckSum = 0;
}

void* CRC32Calc::threadFunc(void * arg)
{
/*	struct temp obj;
		obj.thisPtr = (*(struct temp*)arg).thisPtr;
		obj.flag = (*(struct temp *)arg).flag;

	reinterpret_cast<CRC32Calc*>(obj.thisPtr)->crc32file(obj.flag);
*/

//	reinterpret_cast<CRC32Calc*>( (*(struct temp*)arg).thisPtr)->crc32file( (*(struct temp *)arg).flag);

	reinterpret_cast<CRC32Calc*>(arg)->crc32file(0);
}

bool CRC32Calc::calcCheckSum()
{

	pthread_t thread[2];
	void* exit_status[2];
	
	int flag;
	
	flag = 0;
	
	struct temp obj;
	obj.thisPtr = this;
	obj.flag = flag;

	pthread_create(&thread[0], NULL, &CRC32Calc::threadFunc, this);

	flag = 1;
	pthread_create(&thread[1], NULL, &CRC32Calc::threadFunc, this);


	pthread_join(thread[0], &exit_status[0]);
	pthread_join(thread[1], &exit_status[1]);


	if(sourceCheckSum == destCheckSum)
		return true;

return false;
}



int CRC32Calc::crc32file( int id )
{
	const char *name;
	
	switch(id)
	{
		case 0 :
			name = sourceFilePath.c_str();
			break;
		
		case 1 :
			name - destFilePath.c_str();
			break;
	}; 	
	
	
      register FILE *fin;
      register unsigned long oldcrc32;
      register unsigned long crc32;
      register unsigned long oldcrc;
      register int c;
      register long charcnt;

      oldcrc32 = 0xFFFFFFFF; charcnt = 0;
#ifdef MSDOS
      if ((fin=fopen(name, "rb"))==NULL)
#else
      if ((fin=fopen(name, "r"))==NULL)
#endif
      {
            perror(name);
            return ERROR;
      }
      while ((c=getc(fin))!=EOF)
      {
            ++charcnt;
            oldcrc32 = UPDC32(c, oldcrc32);
      }

      if (ferror(fin))
      {
            perror(name);
            charcnt = -1;
      }
      fclose(fin);

      crc32 = oldcrc32;  oldcrc = oldcrc32 = ~oldcrc32;

/**/
      crc32 = UPDC32((oldcrc32 & 0377), crc32);  oldcrc32 >>=8;
      crc32 = UPDC32((oldcrc32 & 0377), crc32);  oldcrc32 >>=8;
      crc32 = UPDC32((oldcrc32 & 0377), crc32);  oldcrc32 >>=8;
      crc32 = UPDC32((oldcrc32 & 0377), crc32);  oldcrc32 >>=8;
     // printf("%08lX ", crc32);
/**/
	
	switch(id)
	{
		case 0 :
			sourceCheckSum = crc32;
			break;
		case 1 : 
			destCheckSum = crc32;
			break;
	};

    // printf("%08lX %7ld %s\n", oldcrc, charcnt, name
      return OK;
}


/*
int main(int argc, char *argp[])
{
      register int errors = 0;

      while(--argc > 0)
            errors |= crc32file( *++argp);
      return(errors != 0);
}

*/
