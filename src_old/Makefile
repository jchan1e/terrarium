#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG= -O3 -Wall
LIBS=-lglut32cu -lglu32 -lopengl32
CLEAN=del *.exe *.o *.a
else
#  OSX
ifeq ("$(shell uname)","Darwin")
CFLG=-g -O3 -Wall -Wno-deprecated-declarations $(shell sdl2-config --cflags)
LIBS=-framework OpenGL $(shell sdl2-config --libs)
#  Linux/Unix/Solaris
else
CFLG=-g -O3 -Wall $(shell sdl2-config --cflags) -DGL_GLEXT_PROTOTYPES
LIBS=-lGLU -lGL -lm $(shell sdl2-config --libs)
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -rf run *.o *.a *.dSYM
endif

all:run

#  Compile
#.c.o:
#	gcc -std=c99 -c $(CFLG) $<
#.cpp.o:
#	g++ -c $(CFLG) $<
game.o:game.cpp map.h enemy.h tower.h objects.h pixlight.vert pixlight.frag gaussian.frag blender.frag
	g++ -std=c++11 -c $(CFLG) $<

structures.o:structures.cpp structures.h objects.h
	g++ -std=c++11 -c $(CFLG) $<

map.o:map.cpp map.h
	g++ -std=c++11 -c $(CFLG) $<

enemy.o:enemy.cpp enemy.h
	g++ -std=c++11 -c $(CFLG) $<

tower.o:tower.cpp tower.h enemy.h
	g++ -std=c++11 -c $(CFLG) $<

objects.o: objects.cpp objects.h
	g++ -c $(CFLG) $<
#	gcc -std=c99 -c $(CFLG) $<

text.o: text.cpp text.h
	g++ -c $(CFLG) $<

#  link
run:game.o map.o enemy.o tower.o objects.o text.o
	g++ -g -o run $^ $(LIBS) -lSDL2_ttf -I/usr/local/include -I/usr/local/include/cppconn -lmysqlcppconn
	#g++ -g -o run $^ $(LIBS) -lSDL2_ttf -I/usr/local/include -I/usr/local/include/cppconn -lmysqlcppconn

#  Clean
clean:
	$(CLEAN)
