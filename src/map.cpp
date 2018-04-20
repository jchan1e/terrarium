#include "map.h"
#include "objects.h"
#include <iostream>

Map::Map(int W, int H, int seed) {
  srand(seed);
  Width = W;
  Height = H;
  heightmap = new float*[Width];
  for(int i=0; i < Width; ++i)
    heightmap[i] = new float[Height];
  generate();
}

Map::Map(int W, int H) {
  Width = W;
  Height = H;
  heightmap = new float*[Width];
  for(int i=0; i < Width; ++i)
    heightmap[i] = new float[Height];
  generate();
}

Map::~Map() {
  for(int i=0; i < Width; ++i) {
    delete heightmap[i];
    delete grid[i];
  }
  delete[] heightmap;
  delete[] grid;
}

void Map::generate() {
  // generates Perlin Noise to fill grid

  // Initialize and set all values to 0.0
  float ** delta = new float*[Width];
  for(int i=0; i < Width; ++i) {
    delta[i] = new float[Height];
    for(int j=0; j < Height; ++j) {
      heightmap[i][j]= 0.0;
      delta[i][j] = 0.0;
    }
  }

  // Generate 16-scale noise
  for(int i=0; i < Width; i += 16) {
    for(int j=0; j < Height; j += 16) {
      delta[i][j] = (float)rand()/RAND_MAX - 0.5;
    }
  }
  for(int i=0; i < Width; ++i) {
    for(int j=0; j < Height; ++j) {
      int li = 16*(i/16);
      int hi = li+16;
      int lj = 16*(j/16);
      int hj = lj+16;
      float LL = delta[li][lj];
      float LH = 0.0;
      float HL = 0.0;
      float HH = 0.0;
      if (hj < Height)
        LH = delta[li][hj];
      if (hi < Width)
        HL = delta[hi][lj];
      if (hi < Width && hj < Height)
        HH = delta[hi][hj];
      float M1 = LL + (i%16)/(float)16 * (LH-LL);
      float M2 = HL + (i%16)/(float)16 * (HH-HL);
      delta[i][j] = M1 + (j%16)/(float)16 * (M2-M1);
    }
  }
  for(int i=0; i < Width; ++i) {
    for(int j=0; j < Height; ++j) {
      heightmap[i][j] += delta[i][j];
    }
  }

  // Generate 8-scale noise
  for(int i=0; i < Width; i += 8) {
    for(int j=0; j < Height; j += 8) {
      delta[i][j] = ((float)rand()/RAND_MAX - 0.5)/2.0;
    }
  }
  for(int i=0; i < Width; ++i) {
    for(int j=0; j < Height; ++j) {
      int li = 8*(i/8);
      int hi = li+8;
      int lj = 8*(j/8);
      int hj = lj+8;
      float LL = delta[li][lj];
      float LH = 0.0;
      float HL = 0.0;
      float HH = 0.0;
      if (hj < Height)
        LH = delta[li][hj];
      if (hi < Width)
        HL = delta[hi][lj];
      if (hi < Width && hj < Height)
        HH = delta[hi][hj];
      float M1 = LL + (i%8)/(float)8 * (LH-LL);
      float M2 = HL + (i%8)/(float)8 * (HH-HL);
      delta[i][j] = M1 + (j%8)/(float)8 * (M2-M1);
    }
  }
  for(int i=0; i < Width; ++i) {
    for(int j=0; j < Height; ++j) {
      heightmap[i][j] += delta[i][j];
    }
  }

  // Generate 4-scale noise
  for(int i=0; i < Width; i += 4) {
    for(int j=0; j < Height; j += 4) {
      delta[i][j] = ((float)rand()/RAND_MAX - 0.5)/4.0;
    }
  }
  for(int i=0; i < Width; ++i) {
    for(int j=0; j < Height; ++j) {
      int li = 4*(i/4);
      int hi = li+4;
      int lj = 4*(j/4);
      int hj = lj+4;
      float LL = delta[li][lj];
      float LH = 0.0;
      float HL = 0.0;
      float HH = 0.0;
      if (hj < Height)
        LH = delta[li][hj];
      if (hi < Width)
        HL = delta[hi][lj];
      if (hi < Width && hj < Height)
        HH = delta[hi][hj];
      float M1 = LL + (i%4)/(float)4 * (LH-LL);
      float M2 = HL + (i%4)/(float)4 * (HH-HL);
      delta[i][j] = M1 + (j%4)/(float)4 * (M2-M1);
    }
  }
  for(int i=0; i < Width; ++i) {
    for(int j=0; j < Height; ++j) {
      heightmap[i][j] += delta[i][j];
    }
  }

  // Generate 2-scale noise
  for(int i=0; i < Width; i += 2) {
    for(int j=0; j < Height; j += 2) {
      delta[i][j] = ((float)rand()/RAND_MAX - 0.5)/4.0;
    }
  }
  for(int i=0; i < Width; ++i) {
    for(int j=0; j < Height; ++j) {
      int li = 2*(i/2);
      int hi = li+2;
      int lj = 2*(j/2);
      int hj = lj+2;
      float LL = delta[li][lj];
      float LH = 0.0;
      float HL = 0.0;
      float HH = 0.0;
      if (hj < Height)
        LH = delta[li][hj];
      if (hi < Width)
        HL = delta[hi][lj];
      if (hi < Width && hj < Height)
        HH = delta[hi][hj];
      float M1 = LL + (i%2)/(float)2 * (LH-LL);
      float M2 = HL + (i%2)/(float)2 * (HH-HL);
      delta[i][j] = M1 + (j%2)/(float)2 * (M2-M1);
    }
  }
  for(int i=0; i < Width; ++i) {
    for(int j=0; j < Height; ++j) {
      heightmap[i][j] += delta[i][j];
    }
  }

  // Initialize grid
  grid = new Tile*[Width];
  for(int i=0; i < Width; ++i) {
    grid[i] = new Tile[Height];
    for(int j=0; j < Height; ++j) {
      if (heightmap[i][j] > 0.0) {
        grid[i][j] = Tile();
      }
      else {
        grid[i][j] = Tile();
      }
    }
  }

  for(int i=0; i < Width; ++i)
    delete delta[i];
  delete[] delta;
}

void Map::animate() {
  for (int i=0; i < Width; ++i) {
    for (int j=0; j < Height; ++j) {
      //grid[i][j].grow();
    }
  }
}

void Map::render() {
  glPushMatrix();
  glScalef(1,1,2);

  for (int i=0; i < Width; ++i) {
    for (int j=0; j < Height; ++j) {
      float corners[4];
      corners[0] = heightmap[i][j];
      float n = 1.0;
      if (i > 0 && j > 0) {
        corners[0] = (corners[0]*n + heightmap[i-1][j-1]) / (n+1.0);
        n += 1.0;
      }
      if (i > 0) {
        corners[0] = (corners[0]*n + heightmap[i-1][j]) / (n+1.0);
        n += 1.0;
      }
      if (j > 0) {
        corners[0] = (corners[0]*n + heightmap[i][j-1]) / (n+1.0);
      }

      corners[1] = heightmap[i][j];
      n = 1.0;
      if (i > 0 && j < Height-1) {
        corners[1] = (corners[1]*n + heightmap[i-1][j+1]) / (n+1.0);
        n += 1.0;
      }
      if (i > 0) {
        corners[1] = (corners[1]*n + heightmap[i-1][j]) / (n+1.0);
        n += 1.0;
      }
      if (j < Height-1) {
        corners[1] = (corners[1]*n + heightmap[i][j+1]) / (n+1.0);
      }
      
      corners[2] = heightmap[i][j];
      n = 1.0;
      if (i < Width-1 && j < Height-1) {
        corners[2] = (corners[2]*n + heightmap[i+1][j+1]) / (n+1.0);
        n += 1.0;
      }
      if (i < Width-1) {
        corners[2] = (corners[2]*n + heightmap[i+1][j]) / (n+1.0);
        n += 1.0;
      }
      if (j < Height-1) {
        corners[2] = (corners[2]*n + heightmap[i][j+1]) / (n+1.0);
      }

      corners[3] = heightmap[i][j];
      n = 1.0;
      if (i < Width-1 && j > 0) {
        corners[3] = (corners[3]*n + heightmap[i+1][j-1]) / (n+1.0);
        n += 1.0;
      }
      if (i < Width-1) {
        corners[3] = (corners[3]*n + heightmap[i+1][j]) / (n+1.0);
        n += 1.0;
      }
      if (j > 0) {
        corners[3] = (corners[3]*n + heightmap[i][j-1]) / (n+1.0);
      }

      float centerw = -Width/2;
      float centerh = -Height/2;
      glBegin(GL_TRIANGLE_FAN);
      glColor3f(0.5,0.6,0.6);
      glVertex3f(i+centerw,     j+centerh,     heightmap[i][j]);
      glVertex3f(i+centerw-0.5, j+centerh-0.5, corners[0]);
      glVertex3f(i+centerw-0.5, j+centerh+0.5, corners[1]);
      glVertex3f(i+centerw+0.5, j+centerh+0.5, corners[2]);
      glVertex3f(i+centerw+0.5, j+centerh-0.5, corners[3]);
      glVertex3f(i+centerw-0.5, j+centerh-0.5, corners[0]);
      glEnd();
      //std::cout << i+centerw << " " << j+centerh << std::endl;
    }
  }
  glPopMatrix();
}
