#ifndef ANT_H
#define ANT_H

#include "map.h"
#include "net.h"
#include "genome.h"
#include "objects.h"
#include "renderable.h"
#include <cmath>

class Ant : public Renderable
{
public:
  float x, y, z;
  float theta;
  float speed;
  Map* m;
  bool locked;
  std::vector <Ant*> neighbors;

  float getX();
  float getY();
  void setY(float Y);
  void setX(float X);
  float getTheta();
  void setTheta(float th);
  bool isLocked();

  Ant(float X, float Y, Map* M);
  ~Ant();

  //Interface methods
  void render();
  void animate();

  void move(float velocity, float Th);
  void lock();
  void unlock();
  void getNeighbors(float radius);
};

#endif
