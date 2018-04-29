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
  dx = 0;
  dy = 0;
  //theta = (float)rand()/RAND_MAX * M_PI * 2;
  //speed = 0;
}

Ant::~Ant() {
}

void Ant::render() {
  // transform size & location
  glPushMatrix();
  glTranslated(x, y, 0);
  //glRotated(0, 0, 1, theta);

  octahedron(0,0,0, 0, 0.25);
  //and other stuff

  //glTranslatef(cos(theta), sin(theta), 0);
  ////circle(m_radius)
  glPopMatrix();
}

void Ant::animate() {
  // Update the state of this ant by one timestep
}
