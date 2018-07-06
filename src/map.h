#ifndef MAP_H
#define MAP_H

#include "stdGL.h"
#include "tile.h"
#include "renderable.h"
#include <cstdlib>
#include <vector>
#include <queue>

class Ant;

struct point
{
  int x;
  int y;
  
};

class Map : public Renderable {
public:

  int Width;
  int Height;
  std::vector<Ant*>** grid;
  std::vector<Ant*> ants;
  float** elevationmap;
  int** topoMap;
  bool** foundMap;
  std::vector<point*> towerVec;

  //Interface methods
  void render();
  void animate();

  Map(int W, int H);
  ~Map();
  void generate();

  int getW();
  int getH();
  void setW(int W);
  void setH(int H);
  float getElevation(float x, float y);
  void updateTopo();
  void resetFound();
  point* findTallest();
  void updateFound(point* val);
  void bfsTowers(point* maxTower, std::queue<point*> towerFound);
  void getNeighbors(float x, float y, float z, float radius, std::vector<Ant*>* neighbors);
  void addAnt(Ant* ant);
  void setTile(Ant* ant, float antsize, bool lock);

};

#endif
