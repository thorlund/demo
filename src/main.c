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
//  
//  glPopMatrix();
//}


int main() {
  initialize();
  create(800, 480);

  while (1) {
    render();
    update(); /* Swap buffers, clear bits, exit on escape. */
  }

  return 0;
}
