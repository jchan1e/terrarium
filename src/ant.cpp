#include "ant.h"
#include "stdGL.h"

using namespace std;

//Constructor
Ant::Ant(float X, float Y, Map* M) {
    setMap(M);
    setX(X);
    setY(Y);
    setZ(getElevation());
    setSpeed(0.01);
    setDX(0);
    setDY(0);
    setSize(.25);

}

//Destructor
Ant::~Ant() {
}

void Ant::normalize() {
    float oldDX = getDX(), oldDY = getDY();
    float length = sqrt(oldDX*oldDX + oldDY*oldDY);
    setDX(oldDX/length);
    setDY(oldDY/length);
}

//Getters
float Ant::getX() { return x; }
float Ant::getY() { return y; }
float Ant::getDX() { return dx; }
float Ant::getDY() { return dy; }
float Ant::getZ() { return z; }
float Ant::getSize() { return size; }
float Ant::getSpeed() { return speed; }
bool Ant::isLocked() { return locked; }
float Ant::getElevation() {
    return m->getElevation(x, y);
}
float Ant::getElevation(float X, float Y) {
    return m->getElevation(X, Y);
}


//Setters
void Ant::setX(float X) { x = X; }
void Ant::setY(float Y) { y = Y; }
void Ant::setDX(float DX) { dx = DX; }
void Ant::setDY(float DY) { dy = DY; }
void Ant::setZ(float Z) { z = Z; }
void Ant::setSpeed(float V) { speed = V; }
void Ant::setSize(float s) { size = s; }
void Ant::lock() { locked = true; }
void Ant::unlock() { locked = false; }
void Ant::setMap(Map* M) { m = M; }

//For when ants lock and need to update the map
void Ant::setTile(float antsize, bool lock) {
    m->setTile(this, antsize, lock);
}

//Interface methods
void Ant::render() {
    // transform size & location
    glPushMatrix();
    glTranslated(getX()-m->getW()/2, getY()-m->getH()/2, getZ()+getSize());
    //glRotated(0, 0, 1, theta);
    glScalef(2.0,2.0,2.0);
    glColor3f(0.4, 0.2, 0.22);
    octahedron(0,0,0, 0, 0.25);

    //glTranslatef(cos(theta), sin(theta), 0);
    ////circle(m_radius)
    glPopMatrix();
}

void Ant::animate() {
    // Update the state of this ant by one timestep
    getNeighbors(3);
    if(!isLocked()){
        if (!neighbors.empty()) {
            computeCohesion(.1);
            computeAlignment(2);
            computeSeparation(1.5, 1);
            setRandomV(.25);
        } else {
            setRandomV();
        }
        move();
        randomStopProb(10);
    } else {
        randomGoProb(10);
        neighborGoProb(1,10);
    }
}


//Animate methods
void Ant::move() {
    float newx = getX() + getSpeed()*getDX();
    float newy = getY() + getSpeed()*getDY();
    float newz;

    if (newx <= 1) {
        newx = m->getW()-1;
    } else if (newx >= m->getW() - 1 ) {
        newx = 1;
    } if (newy <= 1) {
        newy = m->getH()-1;
    } else if (newy >= m->getH() - 1 ) {
        newy = 1;
    }
    if (getZ() > getElevation(getX(), getY())) {
        newz = getZ() - 4*getSpeed();
    } else {
        newz = getElevation(newx, newy);
    }
    if (newz - getZ() <= 1*getSize()) {
        setX(newx);
        setY(newy);
        setZ(newz);
    } else {
        neighborStopProb(1, 10);
    }

}

void Ant::getNeighbors(float radius) {
    neighbors.clear();
    m->getNeighbors(getX(), getY(), getZ(), radius, &neighbors); //Array of ant pointers
}

//Boids stuff
void Ant::computeAlignment(float weight) {
    if (!neighbors.empty()) {
        float newDX = 0, newDY = 0;
        float n = neighbors.size();

        for (Ant* neighbor : neighbors) {
            newDX += neighbor->getDX();
            newDY += neighbor->getDY();
        }

        setDX(getDX() + weight * newDX/n);
        setDY(getDY() + weight * newDY/n);

        normalize();
    }
}

void Ant::computeSeparation(float radius, float weight) {
    if (!neighbors.empty()) {
        float mx = 0, my = 0;
        float n = neighbors.size();

        for (Ant* neighbor : neighbors) {
                float delx = neighbor->getX() - getX();
                float dely = neighbor->getY() - getY();
                if (sqrt(delx*delx + dely*dely) < radius) {
                    mx += delx;
                    my += dely;

            }

        }

        float newDX = mx/n;
        float newDY = my/n;

        setDX(getDX() - weight * newDX);
        setDY(getDY() - weight * newDY);

        normalize();
    }
}

void Ant::computeCohesion(float weight) {
    if (!neighbors.empty()) {
        float mx = 0, my = 0;
        float n = neighbors.size();

        for (Ant* neighbor : neighbors) {
            mx += neighbor->getX();
            my += neighbor->getY();
        }

        float newDX = mx/n - getX();
        float newDY = my/n - getY();

        setDX(getDX() + weight * newDX);
        setDY(getDY() + weight * newDY);

        normalize();
    }
}

void Ant::setRandomV() { //sets dx, dy to random direction
    setDX((getDX() + -1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2)))));
    setDY((getDY() + -1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2)))));
    normalize();
}

void Ant::setRandomV(float noise) { //sets dx, dy to random direction
    setDX((getDX() + -noise + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2*noise)))));
    setDY((getDY() + -noise + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2*noise)))));
    normalize();
}

void Ant::setStop(){//sets ant tangential movement to zero
  setDY(0);
  setDX(0);
}

void Ant::randomStopProb(int prob1){//random stopping of an ant
  int rNum = rand() % prob1;
  if(rNum == 1){
    setStop();
    setTile(getSize(), true);//boolean for locking position of ants
  }
}

void Ant::randomGoProb(int prob2){//random unlock of ant
  int rNum = rand() % prob2;
  if(rNum == 1){
    setTile(getSize(), false);
  }
}

void Ant::neighborStopProb(float weight, int prob){//stopping of ants based on if neighbors are stopped or not
  int count = 0;
  if(!neighbors.empty()){
    for(Ant* neighbor : neighbors){
      if(neighbor->isLocked()){
        count++;
      }
    }
    int rNum = rand() % prob;
    int var = count*weight;
    if(var >= rNum){
      setStop();
      setTile(getSize(), true);
    }

    }
}

void Ant::neighborGoProb(float weight, int prob) { //unlocking of stopped ants based on neighbor ants who are also unlocked
  int count = 0;
  if(!neighbors.empty()){
    for(Ant* neighbor : neighbors){
      if(!neighbor->isLocked()){
        count++;
      }
    }
    int rNum = rand() % prob;
    int var = count*weight;
    if(var>=rNum){
      setTile(getSize(), false);
    }

  }
}
