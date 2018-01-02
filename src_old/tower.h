#include "objects.h"
#include "enemy.h"

#ifndef tower_h
#define tower_h

class Bullet
{
public:
    float x, y, z, dx, dy, dz, speed;
    int dmg;
    Enemy** target;

    Bullet(float X, float Y, float Z, Enemy** Target);
    void render();
    void animate();
    void collide();
    float distance();
    void normalizeV();
};

class Tower
{
public:
    float x, y, z, dx, dy, dz, range;
    Enemy** target;
    int cooldown, maxcooldown;
    bool wireframe;

    Tower(float X, float Y, bool mode);
    void animate();
    void render();
    Bullet* fire();
    float distance(Enemy** Target);
};

#endif
