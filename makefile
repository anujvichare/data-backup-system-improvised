#makefile to build, clean and run a project

DEP_HEADER =  header_files/log_writer.h header_files/tree_scanner.h header_files/data_copy.h header_files/pipe_requirements.h

%.o: %.cc $(DEP_HEADER)
	g++ -g -c -o $@ $<

build: log_writer.o tree_scanner.o main.o data_copy.o pipe_handler.o
	
	g++ -g -o run.out log_writer.o tree_scanner.o data_copy.o pipe_handler.o main.o
	rm *.o
clean: 
	rm *log *out

run:
	./run.out 

git-pull:
	git pull origin master

git-push:
	git push origin master

usage: 
	@echo "make build <enter> (is to build the project) \n"
	@echo "make clean <enter> (is to clean all logs and executables) \n"
	@echo "make git-pull <enter> (is to pull from master branch Github repo.) \n"
	@echo "make git-push <enter> (is to push work on GitHub repo on master branch) \n"

