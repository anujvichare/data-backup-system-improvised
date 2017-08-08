#include<iostream>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>

#include"log_writer.h"
#include"pipe_requirments.h"

using namespace std;


int stat_status;
struct stat stat_buf;

int temp_no_of_files;

