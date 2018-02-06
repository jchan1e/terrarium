#ifndef TILE_H
#define TILE_H

class Tile {
private:
  bool water;
  float hue;
  float food;
  float maxFood;
  float eatRate;
  float regrowth;
  float meat;

public:
  Tile(float H, float MaxF, float Regr);
  Tile();
  float getFood();
  float getHue();
  void grow();
  float eat();
};

#endif
