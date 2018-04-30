#include "ant.h"
#include "stdGL.h"

using namespace std;

//Constructor
Ant::Ant(float X, float Y, Map* M) {
    setMap(M);
    setX(X);
    setY(Y);
    setZ(m->getHeight(x,y));
    setSpeed(0.05);
    setDX(0);
    setDY(0);

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
    normalize();
}
void Ant::setZ(float Z) { z = Z; }
void Ant::setSpeed(float V) { speed = V; }
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
    getNeighbors(6);
    if (!neighbors.empty()) {
        computeCohesion(0);
        computeAlignment(0);
        computeSeparation(1, 0);
    } else {
        setRandomV();
    }
    move();
}


//Animate methods
void Ant::move() {
    float newx = getX() + getSpeed()*getDX();
    float newy = getY() + getSpeed()*getDY();

    if (newx >= m->getH() || newx <= 0){
        setDX(-getDX());
        newx = getX() + getSpeed()*getDX();
    } if (newy >= m->getW() || newy <= 0){
        setDY(-getDY());
        newy = getY() + getSpeed()*getDY();

    }
    setX(newx);
    setY(newy);
    setZ(m->getHeight(getX(),getY()));
}

void Ant::getNeighbors(float radius) {
    neighbors.clear();
    m->getNeighbors(getX(), getY(), radius, &neighbors); //Array of ant pointers
}

//Boids stuff
void Ant::computeAlignment(float weight) {
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
                mx -= delx;
                my -= dely;
            }

        }

        float newDX = mx/n - getX();
        float newDY = my/n - getY();

        setDX(getDX() - newDX);
        setDY(getDY() - newDY);

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

        setDX(getDX() + newDX);
        setDY(getDY() + newDY);

        normalize();
    }
}
