#include "map.h"
#include "net.h"
#include "genome.h"
#include "objects.h"
#include "renderable.h"

#ifndef CREATURE_H
#define CREATURE_H

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
  bool isLocked();
  Ant(float X, float Y, Map* M);
  ~Ant();
  void render();
  void animate();
  void move(float velocity, float Th);
  float getTheta();
  void setTheta(float th);
  void lock();
  void unlock();
  void getNeighbors();
};

#endif
