#include "stdGL.h"
#include "tile.h"
#include "renderable.h"
#include <cstdlib>

#ifndef MAP_H
#define MAP_H

class Map : public Renderable {
public:
  int Width;
  int Height;
  Tile** grid;
  float** heightmap;

  void render();
  void animate();
  Map(int W, int H, int seed);
  Map(int W, int H);
  ~Map();
  void generate();
  void generate(int seed);
};

#endif
