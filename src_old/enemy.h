#include "objects.h"
#include "map.h"

#ifndef enemy_h
#define enemy_h

class Enemy
{
public:
    float x, y, z, dx, dy, theta, speed;
    //float a, b, c, w;
    int health, type;
    float s1, s2, ds1, ds2;
    Position cur;
    Position nxt;
    Map* F;

    Enemy(int X, int Y, int Health, int Type, Map *F);
    void render();
    void animate();
    void damage(int dmg);
};

#endif
