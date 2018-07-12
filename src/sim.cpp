#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
//#include <SDL.h>
//#include <SDL_opengl.h>
#include "map.h"
#include "ant.h"
//#include "renderer.h"

using namespace std;

//////// SDL Init Function ////////

//bool init()
//{
//  bool success = true;
//
//  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
//  {
//    cerr << "SDL failed to initialize: " << SDL_GetError() << endl;
//    success = false;
//  }
//
//  return success;
//}

///////////////////////////////////

int main(int argc, char *argv[])
{
  //Initialize
  int num_args = 2;
  if (argc != num_args)
  {
    cout << "Usage: <><><>\n";
    return argc;
  }
  int sim_duration = stoi(argv[1]);

  srand (static_cast <unsigned> (time(0)));

  std::vector<Ant*> antList;
  //Renderer* R = new Renderer();
  //R->reshape(1920,1080);

  Map* M;
  M = new Map(48,48);
  //R->addObject(M);
  Ant* A;
  TimeSeries* TS;
  TS = new TimeSeries(1000, 48);

  for (int i = 0; i < 1000; i++) {
      float r1 = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/((M->getH()-3))));
      float r2 = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/((M->getW()-3))));
      A = new Ant(r1, r2, M, TS);
      antList.push_back(A);
      //R->addObject(A);
      M->addAnt(A);
  }


  //Timing
  //int r = 0;
  //int dr = 0;
  //int oldr = 0;
  //int Pause = 0;
  int frames = 0;

  //int startuptime = SDL_GetTicks();
  //oldr = startuptime;

  ////////Main Loop////////
  bool quit = false;
  while (!quit)
  {
    quit = frames >= sim_duration;

    for (Ant* a : antList) {
      a->animate();
    }
    
    frames += 1;
  }

  string filename = "out.dat";
  cout << "Shutting Down\n";
  cout << "writing to " << filename << endl;

  TS->writeAll(filename);

  //delete R;
  for (Ant* a : antList) {
    cout << "deleting ant\n";
    delete a;
  }
  cout << "deletin map\n";
  delete M;
  //delete A;
  //SDL_Quit();

  return 0;
}
