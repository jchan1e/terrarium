#include "ant.h"
#include "stdGL.h"

using namespace std;

//Constructor
Ant::Ant(float X, float Y, Map* M) {
    setMap(M);
    setX(X);
    setY(Y);
    setZ(m->getHeight(x,y));
    setSpeed(0.005);
    setDX(1);
    setDY(1);
}

//Destructor
Ant::~Ant() {
}


//Getters
float Ant::getX() { return x; }
float Ant::getY() { return y; }
float Ant::getDX() { return dx; }
float Ant::getDY() { return dy; }
float Ant::getZ() { return z; }
float Ant::getSpeed() { return speed; }
bool Ant::isLocked() { return locked; }

//Setters
void Ant::setX(float X) { x = X; }
void Ant::setY(float Y) { y = Y; }
void Ant::setDX(float DX) { dx = DX; }
void Ant::setDY(float DY) { dy = DY; }
void Ant::setRandomV() { //sets dx, dy to random direction
    setDX((getDX() + -1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2)))));
    setDY((getDY() + -1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2)))));
}
void Ant::setZ(float Z) { z = Z; }
void Ant::setSpeed(float V) {speed = V; }
void Ant::lock() { locked = true; }
void Ant::unlock() { locked = false; }
void Ant::setMap(Map* M) { m = M; }


//Interface methods
void Ant::render() {
    // transform size & location
    glPushMatrix();
    glTranslated(x, y, z);
    //glRotated(0, 0, 1, theta);

    octahedron(0,0,0, 0, 0.25);
    //and other stuff

    //glTranslatef(cos(theta), sin(theta), 0);
    ////circle(m_radius)
    glPopMatrix();
}

void Ant::animate() {
    // Update the state of this ant by one timestep
    getNeighbors(10);
    if (!neighbors.empty()) {
        computeCohesion();
        computeAlignment();
        computeSeparation();
    } else {
        setRandomV();
    }
    move();
}


//Animate methods
void Ant::move() {
    float newx = getX() + getSpeed()*getDX();
    float newy = getY() + getSpeed()*getDY();

    if (newx >= m->getW() || newx <= 0){
        setX(m->getW()-newx);
    } else setX(newx);

    if (newy >= m->getH() || newy <= 0){
        setY(m->getH()-newy);
    } else setY(newy);

    setZ(m->getHeight(getX(),getY()));
}

void Ant::getNeighbors(float radius) {
    neighbors.clear();
    m->getNeighbors(getX(), getY(), radius, &neighbors); //Array of ant pointers
}

//Boids stuff
void Ant::computeAlignment() {
    if (!neighbors.empty()) {
        float newDX = 0;
        float newDY = 0;
        float n = neighbors.size();

        for (Ant* neighbor : neighbors) {
            newDX += neighbor->getDX();
            newDY += neighbor->getDY();
        }

        setDX(getDX() + newDX/n);
        setDY(getDY() + newDY/n);
    }
}

void Ant::computeSeparation() {
    if (!neighbors.empty()) {
        float newDX = 0;
        float newDY = 0;
        float n = neighbors.size();

        for (Ant* neighbor : neighbors) {
            newDX += getX() - neighbor->getX();
            newDY += getY() - neighbor->getY();
        }

        setDX(getDX() - newDX/n);
        setDY(getDY() - newDY/n);
    }
}

void Ant::computeCohesion() {
    if (!neighbors.empty()) {
        float mx = 0, my = 0;
        float n = neighbors.size();

        for (Ant* neighbor : neighbors) {
            mx += neighbor->getX();
            my += neighbor->getY();
        }

        float newDX = mx/n - getX();
        float newDY = my/n - getY();

        setDX(getDX() + newDX);
        setDY(getDY() + newDY);
    }
}
