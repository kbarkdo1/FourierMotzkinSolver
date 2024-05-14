compiler = clang++

make:
	${compiler} -c solver.cpp 
	${compiler} -o solver solver.o
	rm -f %.o

.PHONY: clean
clean:
	@rm -rf *.o
	@rm -rf solver
	