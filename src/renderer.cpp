#include "renderer.h"

void Renderer::reshape(int width, int height) {
  setW(width);
  setH(height);

  // new aspect ratio
  float w2h = (height < 0) ? (double) width/height : 1;
  // set viewport to match new window size
  glViewport(0,0, w,h);

  //adjust projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  int fov = 60;
  int nearPlane = 0.5;
  int farPlane = 80;
  gluPerspective(fov, w2h, nearPlane, farPlane);

  // switch back to modelview matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Renderer::physics() {
  const Uint8* state = SDL_GetKeyboardState(NULL);
  keyStateUpdate(state);

  // adjust eye position
  setTh(getTh() + getDth());
  setPh(getPh() + getDph());
  float z = getZoom();
  setZoom(z < 2.0 ? 2.0 : z + getDzoom());
}

void Renderer::display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // eye position
  float ex = Sin(-getTh())*Cos(getPh())*getZoom();
  float ey = Cos(-getTh())*Cos(getPh())*getZoom();
  float ez = Sin(getPh())*getZoom();
  gluLookAt(ex,ey,ez, 0,0,0, 0,0,Cos(getPh()));

  // render objects
  //useProgram(pixlight);
  //getUniformLocation
  //glUniform1f

  for (Renderable * object : render_objects) {
    object->render();
  }

  // draw light source
  glUseProgram(0);
  glColor3f(1.0,1.0,1.0);
  ball(0.0,0.0,5.0, 0.25);


  // flush to GPU and swap buffers
  glFlush();
  SDL_GL_SwapWindow(window);
}

void Renderer::keyStateUpdate(const Uint8* state) {
  if (state[SDL_SCANCODE_LEFT])
    setDth(-0.1);
  else if (state[SDL_SCANCODE_RIGHT])
    setDth(0.1);
  else
    setDth(0.0);

  if (state[SDL_SCANCODE_UP])
    setDph(-0.1);
  else if (state[SDL_SCANCODE_DOWN])
    setDph(0.1);
  else
    setDph(0.0);

  if (state[SDL_SCANCODE_Z])
    setDzoom(-0.1);
  else if (state[SDL_SCANCODE_X])
    setDzoom(0.1);
  else
    setDzoom(0.0);
}

int Renderer::handleEvents() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        return 1;
        break;
      case SDL_KEYDOWN:
        switch(event.key.keysym.scancode) {
          case SDL_SCANCODE_Q:
            return 1;
            break;
          case SDL_SCANCODE_SPACE:
            Pause();
            break;
          default:
            break;
        }
      case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
          reshape(event.window.data1, event.window.data2);
        break;
    }
  }
}
