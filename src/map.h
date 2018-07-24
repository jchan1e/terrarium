#ifndef MAP_H
#define MAP_H

#include "stdGL.h"
#include "tile.h"
#include "renderable.h"
#include <cstdlib>
#include <vector>

class Ant;

struct Cluster
{
  std::vector<Ant*> clusAnt;  
};


class Map : public Renderable {
public:

  int Width;
  int Height;
  int n;
  std::vector<Ant*>** grid;
  std::vector<Ant*> ants;
  float** elevationmap;
  std::vector<Cluster*> allClusters;

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

  void getNeighbors(float x, float y, float z, float radius, std::vector<Ant*>* neighbors);
  void addAnt(Ant* ant);
  void setTile(Ant* ant, float antsize, bool lock);

  void resetAntFound();
  void findClusters();
  Cluster* newCluster(Ant* ant);
  Cluster* mergeCluster(bool *arr, int n);

};

#endif
