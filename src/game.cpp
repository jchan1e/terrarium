#include "stdGL.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
// For database connection:
//#include <mysql_connection.h>
//#include <cppconn/driver.h>
//#include <cppconn/exception.h>
//#include <cppconn/resultset.h>
//#include <cppconn/statement.h>
//#include <cppconn/prepared_statement.h>
//#include <iomanip>
//#include <sstream>

//#include "CSCIx229.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include "map.h"
#include "ant.h"
#include "renderer.h"
//#include "text.h"

using namespace std;

//GLOBAL VARIABLES//
//running or not
//bool quit = false;
//
////Window Size
//int w = 1920;
//int h = 1080;
//
////eye position and orientation
//double ex = 0;
//double ey = 0;
//double ez = 0;
//double zoom = 24;
//double dzoom = 0;
//double th = 0;
//double ph = 0;
//double dph = 0;
//double dth = 0;
//
////Textures
////unsigned int texture[5];
//
////Shaders
////int shader = 0;
////int filter = 0;
////int blend  = 0;
////unsigned int img, frame;
////int id;
//
////Game Objects
////Ant* ants;
////vector<Ant*> ants;
//Map* M;
//
//////////////////////
////functions that are called ahead of when they're defined
////because C
//void reshape(int width, int height);
//void keyboard(const Uint8* state);

//////// SDL Init Function ////////

bool init()
{
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
  {
    cerr << "SDL failed to initialize: " << SDL_GetError() << endl;
    success = false;
  }

  //*window = SDL_CreateWindow("Terrarium", 0,0, 1920,1080, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  //if (*window == NULL)
  //{
  //  cerr << "SDL failed to create a window: " << SDL_GetError() << endl;
  //  success = false;
  //}

  //*context = SDL_GL_CreateContext(*window);
  //if (*context == NULL)
  //{
  //  cerr << "SDL failed to create OpenGL context: " << SDL_GetError() << endl;
  //  success = false;
  //}
  //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);


  //Vsync
  //if (SDL_GL_SetSwapInterval(1) < 0)
  //{
  //  cerr << "SDL could not set Vsync: " << SDL_GetError() << endl;
////    success = false;
  //}

  //TTF_Font handling
  //if (TTF_Init() < 0)
  //{
  //  cerr << "TTF font library could not be initialized: " << TTF_GetError() << endl;
  //  success = false;
  //}

  //cout << SDL_GetError() << endl;
  return success;
}

///////////////////////////////////

//void display()
//{
//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//  glEnable(GL_DEPTH_TEST);
//  //glEnable(GL_CULL_FACE);
//
//  //reshape(w,h);
//  glMatrixMode(GL_MODELVIEW);
//  glLoadIdentity();
//
//  //view angle
//  ex = Sin(-th)*Cos(ph)*zoom;
//  ey = Cos(-th)*Cos(ph)*zoom;
//  ez = Sin(ph)*zoom;
//
//  gluLookAt(ex,ey,ez, 0,0,0, 0,0,Cos(ph));
//
//  // Object Rendering
//
//  glColor3f(1.0,1.0,1.0);
//  ball(0,0,0, 0.25);
//
//  M->render();
//
//  //glUseProgram(0);
//
//  //Render Text:
//  //string lives = "Life: " + to_string(F.getLives());
//  //string points = "Score: " + to_string(F.getScore());
//  //string money = "Moneys: " + to_string(F.getMoney());
//
//  ////Show lives on screen
//  //RenderText(lives, (SDL_Color){0,0,0}, 20-1, h-h/20+1, h/20, window);
//  //RenderText(lives, (SDL_Color){0,0,0}, 20+1, h-h/20-1, h/20, window);
//  //RenderText(lives, (SDL_Color){255,255,255}, 20, h-h/20, h/20, window);
//
//  ////Show points on screen
//  //RenderText(points, (SDL_Color){0,0,0}, w-301, h-h/20+1, h/20, window);
//  //RenderText(points, (SDL_Color){0,0,0}, w-299, h-h/20-1, h/20, window);
//  //RenderText(points, (SDL_Color){255,255,255}, w-300, h-h/20, h/20, window);
//
//  ////Show money on the screen
//  //RenderText(money, (SDL_Color){0,0,0}, w/2-59, h-h/20+1, h/20, window);
//  //RenderText(money, (SDL_Color){0,0,0}, w/2-61, h-h/20-1, h/20, window);
//  //RenderText(money, (SDL_Color){255,255,255}, w/2-60, h-h/20, h/20, window);
//
//  //swap the buffers
//  glFlush();
//  SDL_GL_SwapWindow(window);
//}
//
//void physics()
//{
//  const Uint8* state = SDL_GetKeyboardState(NULL);
//  keyboard(state);
//
//  //adjust the eye position
//  th += dth;
//  ph += dph;
//  zoom = zoom<2.0?2.0:zoom+dzoom;
//
//}
//
//
//void reshape(int width, int height)
//{
//  w = width;
//  h = height;
//  //new aspect ratio
//  double w2h = (height > 0) ? (double)width/height : 1;
//  //set viewport to the new window
//  glViewport(0,0 , width,height);
//
//  //switch to projection matrix
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//
//  //adjust projection
//  //glOrtho(-w2h, w2h, -1, 1, -1, 1);
//  gluPerspective(60, w2h, 0.5, 20*4);
//
//  //switch back to model matrix
//  glMatrixMode(GL_MODELVIEW);
//  glLoadIdentity();
//}
//
//// Per frame keyboard input here, per keypress input in main()
//void keyboard(const Uint8* state)
//{
//  //if (state[SDL_SCANCODE_ESCAPE])
//  //  quit = true;
//
//  if (state[SDL_SCANCODE_LEFT])
//    dth = -0.10;
//  else if (state[SDL_SCANCODE_RIGHT])
//    dth = 0.10;
//  else
//    dth = 0;
//
//  if (state[SDL_SCANCODE_DOWN])
//    dph = -0.10;
//  else if (state[SDL_SCANCODE_UP])
//    dph = 0.10;
//  else
//    dph = 0;
//
//  if (state[SDL_SCANCODE_Z])
//    dzoom = -0.10;
//  else if (state[SDL_SCANCODE_X])
//    dzoom = 0.10;
//  else
//    dzoom = 0;
//}
//
//// all user interaction goes here
//void handleEvents()
//{
//  SDL_Event event;
//
//  while (SDL_PollEvent(&event))
//  {
//    switch(event.type)
//    {
//      case SDL_QUIT:
//        quit = true;
//        break;
//
//      case SDL_KEYDOWN:
//        switch (event.key.keysym.scancode)
//        {
//          case SDL_SCANCODE_Q:
//           quit = true;
//           break;
//
//          case SDL_SCANCODE_SPACE:
//           Pause = 1 - Pause;
//           break;
//
//          default:
//           break;
//        }
//
//      case SDL_WINDOWEVENT:
//        if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
//        {
//          //cerr << event.window.data1 << " " << event.window.data2 << endl;
//          reshape(event.window.data1, event.window.data2);
//        }
//        break;
//    }
//  }
//}

int main(int argc, char *argv[])
{
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
  M = new Map(48,48, 1729);
  R->addObject(M);
  Ant* A;

  for (int i = 0; i < 100; i++) {
      float r1 = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/((M->getH()-3))));
      float r2 = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/((M->getW()-3))));
      A = new Ant(r1, r2, M);
      R->addObject(A);
      M->addAnt(A);
  }


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
