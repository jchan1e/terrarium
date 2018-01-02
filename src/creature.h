#include "map.h"
#include "net.h"
#include "genome.h"

#ifndef CREATURE_H
#define CREATURE_H

class Creature
{
public:
   float x, y, dx, dy, theta, speed;
   float hue, mhue;
   float health;
   //float atk;
   //float leye, reye;
   Genome g;
   Net net;

   Creature(float X, float Y, float Th, Genome G);
   ~Creature();
   void render();
   void animate();
};

#endif
