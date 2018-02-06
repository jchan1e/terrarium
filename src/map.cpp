#include "map.h"

Map::Map(int Width, int Height, int seed) {
  srand(seed);
  Map(Width, Height);
}

Map::Map(int Width, int Height) {
  width = Width;
  height = Height;
  heightmap = new float*[width];
  for(int i=0; i < width; ++i)
    heightmap[i] = new float[height];
  generate();
}

Map::~Map() {
  for(int i=0; i < width; ++i) {
    delete heightmap[i];
    delete grid[i];
  }
  delete[] heightmap;
  delete[] grid;
}

void Map::generate() {
  // generates Perlin Noise to fill grid

  // Initialize and set all values to 0.0
  float ** delta = new float*[width];
  for(int i=0; i < width; ++i) {
    delta[i] = new float[height];
    for(int j=0; j < height; ++j) {
      heightmap[i][j]= 0.0;
      delta[i][j] = 0.0;
    }
  }

  // Generate 16-scale noise
  for(int i=0; i < width; i += 16) {
    for(int j=0; j < height; j += 16) {
      delta[i][j] = (float)rand()/RAND_MAX - 0.5;
    }
  }
  for(int i=0; i < width; ++i) {
    for(int j=0; j < height; ++j) {
      int li = 16*(i/16);
      int hi = li+16;
      int lj = 16*(j/16);
      int hj = lj+16;
      float LL = delta[li][lj];
      float LH = 0.0;
      float HL = 0.0;
      float HH = 0.0;
      if (hj < height)
        LH = delta[li][hj];
      if (hi < width)
        HL = delta[hi][lj];
      if (hi < width && hj < height)
        HH = delta[hi][hj];
      float M1 = LL + (i%16)/(float)16 * (LH-LL);
      float M2 = HL + (i%16)/(float)16 * (HH-HL);
      delta[i][j] = M1 + (j%16)/(float)16 * (M2-M1);
    }
  }
  for(int i=0; i < width; ++i) {
    for(int j=0; j < height; ++j) {
      heightmap[i][j] += delta[i][j];
    }
  }

  // Generate 8-scale noise
  for(int i=0; i < width; i += 8) {
    for(int j=0; j < height; j += 8) {
      delta[i][j] = ((float)rand()/RAND_MAX - 0.5)/2.0;
    }
  }
  for(int i=0; i < width; ++i) {
    for(int j=0; j < height; ++j) {
      int li = 8*(i/8);
      int hi = li+8;
      int lj = 8*(j/8);
      int hj = lj+8;
      float LL = delta[li][lj];
      float LH = 0.0;
      float HL = 0.0;
      float HH = 0.0;
      if (hj < height)
        LH = delta[li][hj];
      if (hi < width)
        HL = delta[hi][lj];
      if (hi < width && hj < height)
        HH = delta[hi][hj];
      float M1 = LL + (i%8)/(float)8 * (LH-LL);
      float M2 = HL + (i%8)/(float)8 * (HH-HL);
      delta[i][j] = M1 + (j%8)/(float)8 * (M2-M1);
    }
  }
  for(int i=0; i < width; ++i) {
    for(int j=0; j < height; ++j) {
      heightmap[i][j] += delta[i][j];
    }
  }

  // Generate 4-scale noise
  for(int i=0; i < width; i += 4) {
    for(int j=0; j < height; j += 4) {
      delta[i][j] = ((float)rand()/RAND_MAX - 0.5)/4.0;
    }
  }
  for(int i=0; i < width; ++i) {
    for(int j=0; j < height; ++j) {
      int li = 4*(i/4);
      int hi = li+4;
      int lj = 4*(j/4);
      int hj = lj+4;
      float LL = delta[li][lj];
      float LH = 0.0;
      float HL = 0.0;
      float HH = 0.0;
      if (hj < height)
        LH = delta[li][hj];
      if (hi < width)
        HL = delta[hi][lj];
      if (hi < width && hj < height)
        HH = delta[hi][hj];
      float M1 = LL + (i%4)/(float)4 * (LH-LL);
      float M2 = HL + (i%4)/(float)4 * (HH-HL);
      delta[i][j] = M1 + (j%4)/(float)4 * (M2-M1);
    }
  }
  for(int i=0; i < width; ++i) {
    for(int j=0; j < height; ++j) {
      heightmap[i][j] += delta[i][j];
    }
  }

  // Generate 2-scale noise
  for(int i=0; i < width; i += 2) {
    for(int j=0; j < height; j += 2) {
      delta[i][j] = ((float)rand()/RAND_MAX - 0.5)/4.0;
    }
  }
  for(int i=0; i < width; ++i) {
    for(int j=0; j < height; ++j) {
      int li = 2*(i/2);
      int hi = li+2;
      int lj = 2*(j/2);
      int hj = lj+2;
      float LL = delta[li][lj];
      float LH = 0.0;
      float HL = 0.0;
      float HH = 0.0;
      if (hj < height)
        LH = delta[li][hj];
      if (hi < width)
        HL = delta[hi][lj];
      if (hi < width && hj < height)
        HH = delta[hi][hj];
      float M1 = LL + (i%2)/(float)2 * (LH-LL);
      float M2 = HL + (i%2)/(float)2 * (HH-HL);
      delta[i][j] = M1 + (j%2)/(float)2 * (M2-M1);
    }
  }
  for(int i=0; i < width; ++i) {
    for(int j=0; j < height; ++j) {
      heightmap[i][j] += delta[i][j];
    }
  }

  // Initialize grid
  grid = new Tile*[width];
  for(int i=0; i < width; ++i) {
    grid[i] = new Tile[height];
    for(int j=0; j < height; ++j) {
      if (heightmap[i][j] > 0.0) {
        grid[i][j] = Tile();
      }
      else {
        grid[i][j] = Tile();
      }
    }
  }

  for(int i=0; i < width; ++i)
    delete delta[i];
  delete[] delta;
}

void Map::animate() {
  for (int i=0; i < width; ++i) {
    for (int j=0; j < height; ++j) {
      grid[i][j].grow();
    }
  }
}
