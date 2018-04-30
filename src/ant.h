#ifndef ANT_H
#define ANT_H

#include "map.h"
#include "net.h"
#include "genome.h"
#include "objects.h"
#include "renderable.h"
#include <cmath>

class Ant : public Renderable
{
public:

    //Members
    float x, y, z;
    float dx, dy;
    float speed;
    Map* m;
    bool locked;
    std::vector <Ant*> neighbors;

    //Con/Destructor
    Ant(float X, float Y, Map* M);
    ~Ant();

    //Helper function for direction
    void normalize();
    
    //Getters
    float getX();
    float getY();
    float getDX();
    float getDY();
    float getZ();
    float getSpeed();
    bool isLocked();

    //Setters
    void setX(float X);
    void setY(float Y);
    void setDX(float DX);
    void setDY(float DY);
    void setRandomV();
    void setZ(float Z);
    void setSpeed(float V);
    void lock();
    void unlock();
    void setMap(Map* M);

    //Interface methods
    void render();
    void animate();

    //Animate methods
    void move();

    void getNeighbors(float radius);

    //Boid-like behavior
    void computeAlignment();
    void computeSeparation();
    void computeCohesion();
};

#endif
