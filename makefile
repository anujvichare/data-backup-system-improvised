#makefile to build, clean and run a project

DEP_HEADER =  header_files/log_writer.h header_files/tree_scanner.h

%.o: %.cc $(DEP_HEADER)
	g++ -c -o $@ $<

build: log_writer.o tree_scanner.o
	g++ -g -o run.out log_writer.o tree_scanner.o
	rm *.o
clean: 
	rm *log *out

run:
	./run.out 


usage: 
	@echo "make build <enter> (is to build the project) \n"
	@echo "make clean <enter> (is to clean all logs and executables) \n"


