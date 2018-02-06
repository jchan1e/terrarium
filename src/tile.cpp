#include "tile.h"

Tile::Tile(float H, float MaxF, float Regr) {
  water = false;
  hue = H;
  maxFood = MaxF;
  regrowth = Regr;
  eatRate = 10.0;
  food = maxFood;
  meat = 0;
}

Tile::Tile() {
  water = true;
  hue = 0;
  maxFood = 0;
  regrowth = 0;
  eatRate = 0;
  food = 0;
  meat = 0;
}

float Tile::getFood() {
  return food;
}

float Tile::getHue() {
  return hue;
}

void Tile::grow() {
  if (!water) {
    if (food < maxFood) {
      food += regrowth;
    }
  }
}

float Tile::eat() {
  food -= eatRate;
  return eatRate;
}
