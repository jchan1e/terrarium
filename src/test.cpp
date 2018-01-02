#include <cstdlib>
#include <cstdio>
#include <cmath>

#include "genome.h"
#include "net.h"
#include "map.h"
#include "creature.h"

using namespace std;

int main() {
  // Map Tests
  bool mapsuccess = true;
  Map M(128, 128);
  if (M.width != 128 || M.height != 128) {
    mapsuccess = false;
    printf("Map height/width incorrect\n");
  }
  else {
    float mini = INFINITY;
    float maxi = -INFINITY;
    for (int i=0; i < M.height; ++i) {
      for (int j=0; j < M.width; ++j) {
        if (M.grid[i][j] > maxi)
          maxi = M.grid[i][j];
        if (M.grid[i][j] < mini)
          mini = M.grid[i][j];
      }
    }
    if (mini < -1.0 || maxi > 1.0) {
      mapsuccess = false;
      printf("Map values out of range\n");
    }
  }
  if (!mapsuccess)
    printf("Map Passed\n");

  // Net Tests
  float mi1[10][10] = {{0.0},{0.0},{0.0},{0.0},{0.0},{0.0},{0.0},{0.0},{0.0},{0.0}};
  float m1o[10][10] = {{0.0},{0.0},{0.0},{0.0},{0.0},{0.0},{0.0},{0.0},{0.0},{0.0}};
  for (int i=0; i < 10; ++i) {
    mi1[i][i] = 1.0;
  }
  for (int i=0; i < 10; ++i) {
    m1o[i][10-i] = 1.0;
  }

  Net N(10,10,10, (float**)mi1, (float**)m1o);

  float I[10] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9};
  float R[10] = {0.9,0.8,0.7,0.6,0.5,0.4,0.3,0.2,0.1,0.0};
  N.setInput(I);
  N.evaluate();

  bool netsuccess = true;
  bool stati = true;
  bool stat1 = true;
  bool stato = true;

  for (int i=0; i < 10; ++i) {
    if (N.input[i] != I[i])
      stati = false;
    if (N.layer1[i] != I[i])
      stat1 = false;
    if (N.output[i] != R[i])
      stato = false;
  }
  if (!stati) {
    netsuccess = false;
    printf("Net setInput method failed\n");
  }
  if (!stat1) {
    netsuccess = false;
    printf("Net evaluation failed in dot product 1\n");
  }
  if (!stato) {
    netsuccess = false;
    printf("Net evaluation failed in dot product 2\n");
  }
  if (netsuccess)
    printf("Net Passed\n");

  // Genome Tests
  

  return 0;
}
