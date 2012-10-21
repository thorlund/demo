#ifndef MAIN_H
#define MAIN_H

#include <math.h>

#include "lwcdl/display.h"

#include "simplex.h"


void initialize();
void render();
void color();
void terrain(const double *);
int main();

double rotation;

int ticks;


#endif /* MAIN_H */
