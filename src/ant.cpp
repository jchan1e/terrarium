#include "ant.h"
#include "net.h"
#include "map.h"
#include <cmath>
#include "stdGL.h"

using namespace std;

Ant::Ant(float X, float Y, float Th, Genome G) {
  g = G;
  x = X;
  y = Y;
  dx = 0;
  dy = 0;
  theta = (float)rand()/RAND_MAX * M_PI * 2;
  speed = 0;
  net = new Net(g.ni, g.n1, g.no, g.mi1, g.m1o);
}

Ant::~Ant() {
  delete net;
  delete g.mi1;
  delete g.m1o;
}

void Ant::render() {
  // transform size & location
  glPushMatrix();
  glTranslated(x, y, 0);
  glRotated(0, 0, 1, theta);
  octahedron(0,0,0, 0, 0.25);
  //and other stuff

  //glTranslatef(cos(theta), sin(theta), 0);
  ////circle(m_radius)
  glPopMatrix();
}

void Ant::animate() {
  // evaluate the NN
  // outputs from the NN determine the ant's actions
}
