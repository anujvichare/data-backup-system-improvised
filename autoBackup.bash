#!/bin/bash

#
#this script is to take autobackup of prog folder from /home/anuj to /media/anuj/E drive/linuxHomeAutoBackUp
#

BackupPath=/media/anuj/E\ drive/TestDir

Flag=0

ls "$BackupPath" > /dev/null 2>&1
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
#	echo "execution"
	if [ ! -d /home/anuj/DBSlogs ];
	then

		mkdir /home/anuj/DBSlogs
	fi
	/home/anuj/PROGS/Git/data-backup-system-improvised/run.out /home/anuj/PROGS /media/anuj/E\ drive/TestDir

fi

exit 0
