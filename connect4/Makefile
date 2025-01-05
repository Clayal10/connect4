CXXFLAGS = -g -Wall
EXFLAG = -o play
LDFLAGS = -lGL -lGLEW -lglfw -pthread -g


all:
	${CXX} main.cpp game.cpp window_helpers.cpp game_helpers.cpp glad.c ${EXFLAG} ${LDFLAGS}


test:	all
	./a.out
