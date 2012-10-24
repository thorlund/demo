#include "main.h"

void initialize() {
  rotation = 0.;
  ticks = SDL_GetTicks();
}

void scene1(){
glColor3f(205.0f,201.0f,201.0f);
glEnable ( GL_LIGHTING );
glEnable(GL_LIGHT0);
GLfloat lightpos[] = {.5, 1., 1., 1.};
glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
GLfloat white[] = {0.8f, 0.8f, 0.8f, 1.0f};
//GLfloat red[] = {155.0f, 0.0f, 0.0f, 1.f};
glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
glMaterialfv(GL_FRONT, GL_SPECULAR, white);
GLfloat shininess[] = {250};
glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

glColor3f(255.0f,.0f,.0f);
glBegin(GL_POLYGON);
    glVertex3f(-30.f,-30.f,-40.0f);
    glVertex3f(-30.f, 30.f,-40.0f);
    glVertex3f( 30.f,-30.f,-40.0f);
    glVertex3f( 30.f, 30.f,-40.0f);
    glVertex3f(-30.f, 30.f,-40.0f);
glEnd();

glColor3f(0.0f,.0f,255.0f);
glBegin(GL_POLYGON);
    glVertex3f(-50.f,-50.f, 40.0f);
    glVertex3f(-50.f, 50.f, 40.0f);
    glVertex3f(-30.f,-30.f,-40.0f);
    glVertex3f(-30  , 30.f,-40.0f);
    glVertex3f(-50.f, 50.f, 40.0f);
glEnd();


glColor3f(0.0f,255.0f,.0f);
glBegin(GL_POLYGON);
    glVertex3f(50.f, 50.f, 40.0f);
    glVertex3f(50.f,-50.f, 40.0f);
    glVertex3f(30.f, 30.f,-40.0f);
    glVertex3f(30  ,-30.f,-40.0f);
    glVertex3f(50.f,-50.f, 40.0f);
glEnd();

glColor3f(0.0f,255.0f,255.0f);
glBegin(GL_POLYGON);
    glVertex3f( 50.f, 50.f, 40.0f);
    glVertex3f(-50.f, 50.f, 40.0f);
    glVertex3f( -30.f, 30.f,-40.0f);
    glVertex3f( 30  ,30.f,-40.0f);
    glVertex3f( 50.f,-50.f, 40.0f);
glEnd();

glColor3f(255.0f,255.0f,0.0f);
glBegin(GL_POLYGON);
    glVertex3f(-50.f, -50.f, 40.0f);
    glVertex3f( 50.f, -50.f, 40.0f);
    glVertex3f( 30.f, -30.f,-40.0f);
    glVertex3f(-30.f, -30.f,-40.0f);
    glVertex3f(-50.f,  50.f, 40.0f);
glEnd();


//Blu screen of dead
glDisable ( GL_LIGHTING );
glDisable(GL_LIGHT0);
glColor3f(0.0f,.0f,255.0f);
glBegin(GL_POLYGON);
    glVertex3f(-50.f,-50.f,40.0f);
    glVertex3f(-50.f, 50.f,40.0f);
    glVertex3f( 50.f,-50.f,40.0f);
    glVertex3f( 50.f, 50.f,40.0f);
    glVertex3f(-50.f, 50.f,40.0f);
glEnd();

}



void scene2(){

//Blu screen of dead
glDisable ( GL_LIGHTING );
glDisable(GL_LIGHT0);
glColor3f(0.0f,.0f,255.0f);
glBegin(GL_POLYGON);
    glVertex3f(-50.f,-50.f,40.0f);
    glVertex3f(-50.f, 50.f,40.0f);
    glVertex3f( 50.f,-50.f,40.0f);
    glVertex3f( 50.f, 50.f,40.0f);
    glVertex3f(-50.f, 50.f,40.0f);
glEnd();

}

void render() {
  rotation += (double)(ticks - SDL_GetTicks()) * 0.0000000001;
  ticks = SDL_GetTicks();
  
  if(ticks > 13200)
    glTranslated(0.f, 0.f, -70.f);
  else if(ticks > 11200)
    glTranslated(0.f, 0.f, -400.f+ticks/100.f+(ticks-11200)/10.0f);
  else if(ticks > 1000)
    glTranslated(0.f, 0.f, -400.f+ticks/100.f);
  else
    glTranslated(0.f, 0.f, -400.f);
  glPushMatrix();
  //printf("ticks %u\n", ticks);
  

  if(ticks < 13200){
    glRotated((6.28 / 16.) * 360. / 6.28, 1., 0., 0.);
    glRotated(rotation/2, 0., 1., 0.);
  }

  if(ticks < 13200)
    scene1();
  else
    scene2();
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
