#include "stdGL.h"
#include "tile.h"
#include "renderable.h"
#include <cstdlib>
#include "ant.h"

#ifndef MAP_H
#define MAP_H

class Map : public Renderable {
public:

  int Width;
  int Height;
  std::vector<Tile>** grid;
  std::vector<Ant*> ants;
  float** heightmap;

  //Interface methods
  void render();
  void animate();

  Map(int W, int H, int seed);
  Map(int W, int H);
  ~Map();

  void generate();
  void generate(int seed);

  float getHeight(float x, float y);
  int getState(int x, int y);
};

#endif
