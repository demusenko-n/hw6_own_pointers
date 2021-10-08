COMPILER = g++
SOURCES = main.cpp MyShared_ptr.hpp MyUnique_ptr.hpp
EXEC_FILENAME = prog.exe

all: compile
run: compile
	@./${EXEC_FILENAME}
compile:
	${COMPILER} ${SOURCES} -o ${EXEC_FILENAME} -w
clear:
	rm -f *.o ${EXEC_FILENAME}

