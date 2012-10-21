#include "main.h"

void initialize() {
  rotation = 0.;
  ticks = SDL_GetTicks();
}



void scene1() {
  const size_t SIZE = 128;
  size_t i, j;
  double x, z;
  double noise[SIZE][SIZE];

  /* Generate terrain noise. */
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      noise[i][j] = simplexNoise3(4, 0.5, 0.01, (double)i, ticks * 0.01 + 500., (double)j);
    }
  }



  /* Render wireframe terrain. */
  glColor3f(1.f, 1.f, 1.f);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  for (z = 0.; z < (double)SIZE - 1.; z++) {
    double noise0 = noise[0][(int)z] * 16.f;
    double noise1 = noise[0][(int)z+1] * 16.f;
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3d(0., noise0, z);
    glVertex3d(0., noise1, z + 1.);
    for (x = 0.; x < (double)SIZE - 1.; x++) {
      double noise2 = noise[(int)x+1][(int)z] * 16.f;
      double noise3 = noise[(int)x+1][(int)z+1] * 16.f;
      glVertex3d(x + 1., noise2, z);
      glVertex3d(x + 1., noise3, z + 1.);
    }
    glEnd();
  }
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}



void scene2() {
  scene1();

  /* Render water */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4d(0., 0.3, 0.8, (double)(ticks - 10000) * 0.0001);
  glBegin(GL_TRIANGLE_STRIP);
  glVertex3d(0., 1., 0.);
  glVertex3d(0., 1., 127.);
  glVertex3d(127., 1., 0.);
  glVertex3d(127., 1., 127.);
  glEnd();
  glDisable(GL_BLEND);
}



void scene3() {
  scene2();

  /* Render more stuff. */
}



void render() {
  rotation += (double)(ticks - SDL_GetTicks()) * 0.0000000001;
  ticks = SDL_GetTicks();

  glPushMatrix();

  glTranslated(1.f, -8.f, -96.f);
  glRotated((6.28 / 16.) * 360. / 6.28, 1., 0., 0.);
  glRotated(rotation, 0., 1., 0.);
  glTranslated(-64.f, 0.f, -64.f);

  if (ticks < 10000) {
    scene1();
  } else if (ticks < 20000) {
    scene2();
  } else {
    scene3();
  }
  
  glPopMatrix();
}



int main() {
  initialize();
  create(800, 480);

  while (1) {
    render();
    update(); /* Swap buffers, clear bits, exit on escape. */
  }

  return 0;
}
