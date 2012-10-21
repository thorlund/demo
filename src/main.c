#include "main.h"

void initialize() {
  rotation = 0.;
  ticks = SDL_GetTicks();
}

// steenstrupsscreen(float scale){
//    front = [[0.f,0.f],[0.f,2.f],[2.f,0.f],[2.f,2.f]]
//    
//}
//
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    glBegin(GL_POLYGON);
//    glEnd();
void render() {
  rotation += (double)(ticks - SDL_GetTicks()) * 0.0000000001;
  ticks = SDL_GetTicks();

  glPushMatrix();

//  glTranslated(1.f, -8.f, -96.f);
//  glRotated((6.28 / 16.) * 360. / 6.28, 1., 0., 0.);
//  glRotated(rotation, 0., 1., 0.);
//  glTranslated(-64.f, 0.f, -64.f);
//
//  if (ticks < 10000) {
//    scene1();
//  } else if (ticks < 20000) {
//    scene2();
//  } else {
//    scene3();
//  }
  
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
