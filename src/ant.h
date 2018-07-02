#ifndef ANT_H
#define ANT_H

#include "map.h"
#include "data.h"
#include "net.h"
#include "genome.h"
#include "objects.h"
#include "renderable.h"
#include "data.h"
#include <cmath>

class Ant : public Renderable
{
public:

    //Members
    float x, y, z;
    bool dead;
    float dx, dy;
    float speed;
    Map* m;
    bool locked;
    std::vector <Ant*> neighbors;
    float size;
    TimeSeries* ts;
    //Con/Destructor
    Ant(float X, float Y, Map* M, TimeSeries* TS);
    Ant(float X, float Y, Map* M, bool D);
    ~Ant();

    //Helper function for direction
    void normalize();

    //Getters
    float getX();
    float getY();
    float getDX();
    float getDY();
    float getZ();
    float getSize();
    float getSpeed();
    bool isLocked();
    float getElevation();
    float getElevation(float X, float Y);

    //Setters
    void setX(float X);
    void setY(float Y);
    void setDX(float DX);
    void setDY(float DY);
    void setRandomV();
    void setRandomV(float noise);
    void setZ(float Z);
    void setSpeed(float V);
    void setSize(float s);
    void setTile(float antsize, bool lock);
    void lock();
    void unlock();
    void setMap(Map* M);
    void setTS(TimeSeries* TS);
    void setDead(bool D);

    //Interface methods
    void render();
    void animate();

    //Animate methods
    void move();
    void reportCoord();
    void getNeighbors(float radius);


    //Boid-like behavior
    void computeAlignment(float weight);
    void computeSeparation(float radius, float weight);
    void computeCohesion(float weight);

    //More Ant behavior
    void randomStopProb(int prob1);
    void setStop();
    void randomGoProb(int prob2);
    void neighborStopProb(float weight, int prob);
    void neighborGoProb(float weight, int prob);
};

#endif
