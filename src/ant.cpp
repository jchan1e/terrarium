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
  locked = false;
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

void Ant::move(float velocity, float Th) {
     setX(getX() + velocity*cos(Th));
     setY(getY() + velocity*sin(Th));
}

void Ant::lock() {
    locked = true;
}

void Ant::unlock() {
    locked = false;
}

float Ant::getX() { return x; }
float Ant::getY() { return y; }
float Ant::setX(float X) { x = X; }
float Ant::setY(float Y) { y = Y; }
bool Ant::isLocked() { return locked; }

Ant* getLockedNeighbors(float radius) {
    return m->getLockedNeighbors(x, y, radius); //Array of ant pointers
}