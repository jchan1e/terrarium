#include "creature.h"
#include "net.h"
#include "map.h"
#include <cmath>

using namespace std;

Creature::Creature(float X, float Y, float Th, Genome G) {
  g = G;
  x = X;
  y = Y;
  dx = 0;
  dy = 0;
  theta = (float)rand()/RAND_MAX * M_PI;
  speed = 0;
  net = new Net(g.ni, g.n1, g.no, g.mi1, g.m1o);
}

Creature::~Creature() {
  delete net;
  delete g.mi1;
  delete g.m1o;
}

void Creature::render() {
  // do stuff
}

void Creature::animate() {
  // simulation actions go here
}
