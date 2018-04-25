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
#CFLG=-g -O3 -Wall -std=c++11
CFLG=-g -Wall -std=c++11

compile:run

all:run test


test.o:test.cpp map.h net.h genome.h ant.h
	g++ -c $(CFLG) $<

game.o:game.cpp renderer.h map.h net.h genome.h ant.h stdGL.h
	g++ -c $(CFLG) $(SFLG) $<

renderer.o:renderer.cpp renderer.h renderable.h shader.h stdGL.h
	g++ -c $(CFLG) $(SFLG) $<

map.o:map.cpp map.h tile.h
	g++ -c $(CFLG) $<

ant.o:ant.cpp ant.h genome.h net.h map.h stdGL.h
	g++ -c $(CFLG) $<

objects.o:objects.cpp stdGL.h
	g++ -c $(CFLG) $(SFLG) $<

shader.o:shader.cpp shader.h
	g++ -c $(CFLG) $(SFLG) $<

#genome.o:genome.cpp genome.h net.h
#	g++ -c $(CFLG) $<

net.o:net.cpp net.h
	g++ -c $(CFLG) $<

tile.o:tile.cpp tile.h
	g++ -c $(CFLG) $<

text.o:text.cpp text.h stdGL.h
	g++ -c $(CFLG) $<


#  link
run:game.o renderer.o shader.o map.o ant.o net.o objects.o tile.o
	g++ -g -o run $^ $(GLIBS) -lSDL2_ttf
	#g++ -g -O3 -o run $^ $(GLIBS) -lSDL2_ttf

Test:test.o map.o ant.o net.o objects.o tile.o
	g++ -g -O3 -o Test $^ $(GLIBS)

test:FORCE Test 
	./Test

FORCE:


#  Clean
clean:
	$(CLEAN)
