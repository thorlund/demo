#include "display.h"

int width = 800;
int height = 480;

void create() {
  const int BPP = 16;
  const int FLAGS =
    SDL_OPENGL |
    SDL_GL_DOUBLEBUFFER |
    SDL_HWPALETTE |
    SDL_HWACCEL;

  SDL_Init(SDL_INIT_VIDEO);
  atexit(SDL_Quit);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_WM_SetCaption("", 0);
  SDL_SetVideoMode(width, height, BPP, FLAGS);

  glClearColor(0.f, 0.f, 0.f, 1.f);
}

void update() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
      exit(0);
    }
  }
  glFlush();
  SDL_GL_SwapBuffers();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  perspective();
}

void perspective() {
  const float FOV = 45.f;
  const float ASPECT = (float)width / (float)height;
  const float ZNEAR = 0.1f;
  const float ZFAR = 1000.f;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(FOV, ASPECT, ZNEAR, ZFAR);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glEnable(GL_DEPTH_TEST);
}
