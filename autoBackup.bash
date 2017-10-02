#!/bin/bash

#
#this script is to take autobackup of prog folder from /home/anuj to /media/anuj/E drive/linuxHomeAutoBackUp
#

BackupPath=/media/anuj/E\ drive/TestDir

Flag=0

ls "$BackupPath" 2> /dev/null
if [ $? -eq 0 ] 
then	
	Flag=1
else
 	mount /dev/sda6 "/media/anuj/E drive/"
	if [ $? -eq 0 ]
	then 
		Flag=1
	fi
	
fi

if [ $Flag -eq 1 ]
then
	echo "execution"
	./run.out /home/anuj/PROGS /media/anuj/E\ drive/TestDir

fi


