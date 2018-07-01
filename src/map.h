#ifndef MAP_H
#define MAP_H

#include "stdGL.h"
#include "tile.h"
#include "renderable.h"
#include <cstdlib>
#include <vector>

class Ant;


class Map : public Renderable {
public:

  int Width;
  int Height;
  std::vector<Ant*>** grid;
  std::vector<Ant*> ants;
  std::vector<std::vector<Ant*>*>* towers;
  std::vector<Ant*>* ithTower;
  float** elevationmap;
  float maxX, maxY; //x and y values corresponding to maxH


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
  std::vector<Ant*>* getmaxHeight();
  void defineTower(std::vector<Ant*>* antTower);
  void countTowers();
  void setFound();
  void setmaxHeightX(float X);
  void setmaxHeightY(float Y);
  void getNeighbors(float x, float y, float z, float radius, std::vector<Ant*>* neighbors);
  void getAdjacent(Ant* testAnt, float radius, std::vector<Ant*>* adjacent);
  void addAnt(Ant* ant);
  void setTile(Ant* ant, float antsize, bool lock);


};

#endif
