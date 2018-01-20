#makefile to build, clean and run a project

DEP_HEADER =  header_files/log_writer.h header_files/tree_scanner.h header_files/data_copy.h header_files/pipe_requirements.h header_files/crc32_calculator.h

%.o: %.cc $(DEP_HEADER)
	g++ -std=c++11 -g -c -o $@ $<

build: log_writer.o tree_scanner.o main.o data_copy.o pipe_handler.o crc32_calculator.o
	
	g++ -pthread -std=c++11 -g -o run.out crc32_calculator.o log_writer.o tree_scanner.o data_copy.o pipe_handler.o main.o
	rm *.o
clean: 
	rm logs/*log *out

run:
	./autoBackup.bash

git-pull:
	git pull origin master

git-push:
	count=`ls -l logs/*log 2>/dev/null | wc -l`; \
	if [ $$count -ne 0 ]; then \
	   rm logs/*log; \
	fi
	count=`ls -l *out 2>/dev/null | wc -l`; \
	if [ $$count != 0 ]; then \
	   rm *out; \
	fi
	git add .
	git commit -m "${comment}"
	git push origin master

usage: 
	@echo "make build <enter> (is to build the project) \n"
	@echo "make clean <enter> (is to clean all logs and executables) \n"
	@echo "make git-pull <enter> (is to pull from master branch Github repo.) \n"
	@echo "make comment="comment" git-push <enter> (is to push work on GitHub repo on master branch) \n"

