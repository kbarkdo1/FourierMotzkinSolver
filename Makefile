compiler = clang++

make:
	${compiler} -c solver.cpp 
	${compiler} -o solver solver.o
	$ ./solver