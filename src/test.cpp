#include <cstdlib>
#include <cstdio>
#include <cmath>

#include <iostream>

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
      //cout << "| ";
      for (int j=0; j < M.width; ++j) {
        //cout << M.grid[i][j] << " | ";
        if (M.grid[i][j] > maxi)
          maxi = M.grid[i][j];
        if (M.grid[i][j] < mini)
          mini = M.grid[i][j];
      }
      //cout << endl;
    }
    if (mini < -1.0 || maxi > 1.0) {
      mapsuccess = false;
      printf("Map values out of range\n");
    }
  }
  if (mapsuccess)
    printf("Map Passed\n");

  // Net Tests
  float** mi1 = new float*[10];
  float** m1o = new float*[10];
  for (int i=0; i < 10; ++i) {
    mi1[i] = new float[10];
    m1o[i] = new float[10];
    for (int j=0; j < 10; ++j) {
      if (i == j)
        mi1[i][j] = 1.0;
      else
        mi1[i][j] = 0.0;
      if (i + j == 9)
        m1o[i][j] = 1.0;
      else
        m1o[i][j] = 0.0;
    }
  }

  Net N(10,10,10, mi1, m1o);

  float I[10] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9};
  float R[10] = {0.9,0.8,0.7,0.6,0.5,0.4,0.3,0.2,0.1,0.0};
  N.setInput(I);
  N.evaluate();

  bool netsuccess = true;
  bool stati = true;
  bool stat1 = true;
  bool stato = true;

  for (int i=0; i < 10; ++i) {
    if (abs(N.input[i]  - I[i]) > 0.001)
      stati = false;
    if (abs(N.layer1[i] - I[i]) > 0.001)
      stat1 = false;
    if (abs(N.output[i] - R[i]) > 0.001)
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

  // Creature Tests
  //Genome G = {0.333, 0.5, 10, 10, 10, mi1, m1o};
  //Creature C(0.0, 0.0, M_PI/3, G);
  //C.animate();
  // check that it worked

  for (int i=0; i < 10; ++i) {
    delete mi1[i];
    delete m1o[i];
  }
  delete[] mi1;
  delete[] m1o;

  return 0;
}
