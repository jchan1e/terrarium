#include <cstdlib>

#ifndef MAP_H
#define MAP_H

struct Tile
{
   float hue;
   float maximum;
   float regrowth;
};

class Map
{
public:
    int width, height;
    float** grid;

    void render();
    void animate();
    Map(int Width, int Height);
    ~Map();
    void generate();
    void generate(int seed);
};

#endif
