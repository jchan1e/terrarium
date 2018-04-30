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
    float theta;
    float speed;
    Map* m;
    bool locked;
    std::vector <Ant*> neighbors;

    //Con/Destructor
    Ant(float X, float Y, Map* M);
    ~Ant();

    //Getters
    float getX();
    float getY();
    float getZ();
    float getV();
    float getTheta();
    bool isLocked();

    //Setters
    void setX(float X);
    void setY(float Y);
    void setZ(float Z);
    void setV(float V);
    void setTheta(float th);
    void lock();
    void unlock();
    void setMap(Map* M);

    //Interface methods
    void render();
    void animate();

    //Animate methods
    void move(float velocity, float Th);
    void getNeighbors(float radius);

    //Boid-like behavior
    void computeAlignment();
};

#endif
