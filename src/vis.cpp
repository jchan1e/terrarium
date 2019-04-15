#include "stdGL.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SDL.h>
#include <SDL_opengl.h>
#include "map.h"
#include "ant.h"
#include "renderer.h"

using namespace std;

//////// SDL Init Function ////////

bool init()
{
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
  {
    cerr << "SDL failed to initialize: " << SDL_GetError() << endl;
    success = false;
  }

  return success;
}

///////////////////////////////////

int main(int argc, char *argv[])
{
  if(argc < 2)
  {
    cerr << "Requires at least 1 argument\nExiting..\n";
    return 1;
  }

  ifstream F(argv[1]);
  if (!F.is_open())
  {
    cerr << "couldn't open file " << argv[1] << endl;
    return 2;
  }

  //Initialize
  if (init() != true)
  {
    cerr << "Shutting Down\n";
    return 1;
  }

  srand (static_cast <unsigned> (time(0)));

  Renderer* R = new Renderer();
  R->reshape(1920,1080);

  Map* M;
  M = new Map(48,48);
  R->addObject(M);
  Ant* A;

  string S;
  int i = 1;
  string s1, s2, s3;
  float r1, r2, r3;
  while (getline(F,S, ','))
  {
    if (S[0] == '\n')
      S.erase(0,1);
    //string s1 = S.substr(0, S.find(delimiter));
    //string s2 = S.substr(1, S.find(delimiter));
    //string s3 = S.substr(2, S.find(delimiter));
    //float r1 = stof(s1);
    //float r2 = stof(s2);
    //float r3 = stof(s3);
    if (S.length() > 0)
    {
      switch (i)
      {
      case 1:
        s1 = S;
        r1 = stof(s1);
        i = 2;
        S = "";
        break;
      case 2:
        s2 = S;
        r2 = stof(s2);
        i = 3;
        S = "";
        break;
      case 3:
        s3 = S;
        r3 = stof(s3);
        i = 1;
        S = "";
        cout << s1 << ", " << s2 << ", " << s3 << endl;
        //cout << r1 << ", " << r2 << ", " << r3 << endl;
        A = new Ant(r1/2 + M->getW()/2, r2/2 + M->getH()/2, r3, M);
        R->addObject(A);
        M->addAnt(A);
        break;
      }
    }
  }

  //for (int i = 0; i < 1000; i++) {
  //    float r1 = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/((M->getH()-3))));
  //    float r2 = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/((M->getW()-3))));
  //    A = new Ant(r1, r2, M);
  //    R->addObject(A);
  //    M->addAnt(A);
  //}

  //Timing
  int r = 0;
  int dr = 0;
  int oldr = 0;
  //int Pause = 0;
  int frames = 0;

  int startuptime = SDL_GetTicks();
  oldr = startuptime;

  ////////Main Loop////////
  bool quit = false;
  while (!quit)
  {
    //cout << "handling events\n";
    quit = R->handleEvents();

    //// PHYSICS TIMING ////
    r = SDL_GetTicks();
    dr += r - oldr;
    while (dr >= 16)
    {
      //cout << "physics step\n";
      R->physics();
      dr -= 16;
    }
    oldr = r;
    R->display();
    frames += 1;
    //quit = true;
  }

  cout << "Shutting Down\n";
  cout << "average framerate: " << 1000*(float)frames/(r - startuptime) << endl;

  delete R;
  //delete M;
  //delete A;

  SDL_Quit();

  return 0;
}
