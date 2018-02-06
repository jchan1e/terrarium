#include "tile.h"
#include <cstdlib>

#ifndef MAP_H
#define MAP_H

class Map
{
public:
   int width, height;
   Tile** grid;
   float** heightmap;

   void render();
   void animate();
   Map(int Width, int Height, int seed);
   Map(int Width, int Height);
   ~Map();
   void generate();
   void generate(int seed);
};

#endif
