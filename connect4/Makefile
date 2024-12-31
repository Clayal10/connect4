CXXFLAGS = -g -Wall 
EXFLAG = -o play
LDFLAGS = -lglfw -pthread -g 


all:
	${CXX} main.cpp game.cpp glad.c ${EXFLAG} ${LDFLAGS}


test:	all
	./a.out

