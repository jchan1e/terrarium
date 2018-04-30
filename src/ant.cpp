#include "ant.h"
#include "stdGL.h"

using namespace std;

//Constructor
Ant::Ant(float X, float Y, Map* M) {
    setMap(M);
    setX(X);
    setY(Y);
    setZ(m->getHeight(x,y));
    setTheta((float)rand()/RAND_MAX * M_PI * 2);
    setV(0);
}

//Destructor
Ant::~Ant() {
}


//Getters
float Ant::getX() { return x; }
float Ant::getY() { return y; }
float Ant::getZ() { return z; }
float Ant::getV() { return speed; }
float Ant::getTheta() { return theta; }
bool Ant::isLocked() { return locked; }


//Setters
void Ant::setX(float X) { x = X; }
void Ant::setY(float Y) { y = Y; }
void Ant::setZ(float Z) { z = Z; }
void Ant::setV(float V) {speed = V; }
void Ant::setTheta(float th) {
    theta = fmod(th, 2.0*M_PI);
}
void Ant::lock() { locked = true; }
void Ant::unlock() { locked = false; }
void Ant::setMap(Map* M) { m = M; }


//Interface methods
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
    move(getV(), getTheta());
    setZ(m->getHeight(getX(),getY()));
}


//Animate methods
void Ant::move(float velocity, float Th) {
    setX(getX() + velocity*cos(Th));
    setY(getY() + velocity*sin(Th));
}

void Ant::getNeighbors(float radius) {
    neighbors.clear();
    m->getNeighbors(getX(), getY(), radius, &neighbors); //Array of ant pointers
}

//Boids stuff
void Ant::computeAlignment() {
    if (!neighbors.empty()) {
        float newTheta = 0;
        for (Ant* neighbor : neighbors) {
            newTheta += neighbor->getTheta();
        }
        setTheta(newTheta/neighbors.size());
    }
}
