#include "map.h"
#include "net.h"
#include "genome.h"
#include "objects.h"

#ifndef CREATURE_H
#define CREATURE_H

class Ant
{
public:
  float x, y, dx, dy, theta, speed;
  float hue, mhue;
  float health;
  //float atk;
  //float leye, reye;
  Genome g;
  Net* net;

  Ant(float X, float Y, float Th, Genome G);
  ~Ant();
  void render();
  void animate();
};

#endif
