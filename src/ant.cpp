#include "ant.h"
#include "net.h"
#include "map.h"
#include <cmath>
#include "stdGL.h"

using namespace std;

Ant::Ant(float X, float Y, Map* M) {
  m = M;
  x = X;
  y = Y;
  z = m->getHeight(x,y);
  theta = (float)rand()/RAND_MAX * M_PI * 2;
  speed = 0;
}

Ant::~Ant() {
}

void Ant::render() {
  // transform size & location
  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(0, 0, 1, theta);

  octahedron(0,0,0, 0, 0.25);
  //and other stuff

  //glTranslatef(cos(theta), sin(theta), 0);
  ////circle(m_radius)
  glPopMatrix();
}

void Ant::animate() {
  // Update the state of this ant by one timestep
  move(0.005, M_PI/4);
  z = m->getHeight(x, y);
}

void Ant::move(float velocity, float Th) {
     x += velocity*cos(Th);
     y += velocity*sin(Th);
}
