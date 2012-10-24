#include "main.h"

void initialize() {
  rotation = 0.;
  ticks = SDL_GetTicks();
}

void scene1(){
glColor3f(0.0f,0.0f,1.0f);
glEnable ( GL_LIGHTING ) ;
glBegin(GL_POLYGON);
    glVertex3f(-50.f,-50.f,0.0f);
    glVertex3f(-50.f, 50.f,0.0f);
    glVertex3f( 50.f,-50.f,0.0f);
    glVertex3f( 50.f, 50.f,0.0f);
    glVertex3f(-50.f, 50.f,0.0f);
glEnd();
}

void render() {
  rotation += (double)(ticks - SDL_GetTicks()) * 0.0000000001;
  ticks = SDL_GetTicks();

  glTranslated(0.f, 0.f, -400.f+ticks/100.f);
  glPushMatrix();
  
  


  glRotated((6.28 / 16.) * 360. / 6.28, 1., 0., 0.);
  glRotated(rotation, 0., 1., 0.);

  scene1();

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
