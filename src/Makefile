#  MinGW
#ifeq "$(OS)" "Windows_NT"
#SFLG= -O3 -Wall
#LIBS=-lglut32cu -lglu32 -lopengl32
#CLEAN=del *.exe *.o *.a
#else
#  OSX
ifeq ("$(shell uname)","Darwin")
SFLG=-Wno-deprecated-declarations $(shell sdl2-config --cflags)
GLIBS=-framework OpenGL $(shell sdl2-config --libs)
CLEAN=rm -rf run Test *.o *.a *.dSYM
#  Linux/Unix/Solaris
else
SFLG=$(shell sdl2-config --cflags) -DGL_GLEXT_PROTOTYPES
GLIBS=-lGLU -lGL -lm $(shell sdl2-config --libs)
CLEAN=rm -rf run Test *.o *.a
endif
#endif
CFLG=-g -O3 -Wall -std=c++11
#CFLG=-g -Wall -std=c++11

compile:run Test

all:run test


test.o:test.cpp map.h net.h genome.h creature.h
	g++ -c $(CFLG) $<

game.o:game.cpp map.h net.h genome.h creature.h
	g++ -c $(CFLG) $(SFLG) $<

map.o:map.cpp map.h
	g++ -c $(CFLG) $<

creature.o:creature.cpp creature.h genome.h net.h map.h
	g++ -c $(CFLG) $<

#genome.o:genome.cpp genome.h net.h
#	g++ -c $(CFLG) $<

net.o:net.cpp net.h
	g++ -c $(CFLG) $<

text.o:text.cpp text.h
	g++ -c $(CFLG) $<


#  link
run:game.o map.o creature.o net.o
	g++ -g -O3 -o run $^ $(GLIBS) -lSDL2_ttf

Test:test.o map.o creature.o net.o
	g++ -g -o Test $^
	#g++ -g -O3 -o test $^
test: Test
	./Test


#  Clean
clean:
	$(CLEAN)
