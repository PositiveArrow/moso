# Makefile variables
CPP=g++-4.9
#CPPFLAGS=-fdiagnostics-color=auto -std=c++1y -g -O0 -Wall
CPPFLAGS=-fdiagnostics-color=auto -std=c++1y -O3 -Wall
all: ./bin/p1_test

# Main target
./bin/p1_test: ./objs/p1_test.o ./objs/player1.o ./objs/board2.o ./objs/board_common.o Makefile
	$(CPP) $(CPPFLAGS) $(LDFLAGS) -o ./bin/p1_test ./objs/p1_test.o ./objs/player1.o ./objs/board2.o ./objs/board_common.o $(LIBRARIES)

# C++ files to object
./objs/p1_test.o: ./p1_test.cpp ./board2.h ./board_common.h ./player1.h Makefile
	$(CPP) $(CPPFLAGS) $(INCFLGS) -c p1_test.cpp -o ./objs/p1_test.o
./objs/board2.o: ./board2.cpp ./board2.h ./board_common.h Makefile
	$(CPP) $(CPPFLAGS) -c board2.cpp -o ./objs/board2.o
./objs/board_common.o: ./board_common.cpp ./board_common.h Makefile
	$(CPP) $(CPPFLAGS) -c board_common.cpp -o ./objs/board_common.o
./objs/player1.o: ./player1.cpp ./player1.h ./board2.h ./board_common.h Makefile
	$(CPP) $(CPPFLAGS) -c player1.cpp -o ./objs/player1.o
	
clean:
	rm -f ./bin/p1_test ./objs/*.o
   
