/* Simplex.cpp
 *
 * Copyright 2007 Eliot Eshelman
 * battlestartux@6by9.net
 *
 *
 *  This file is part of Battlestar Tux.
 *
 *  Battlestar Tux is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  Battlestar Tux is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Battlestar Tux; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#include <math.h>

#include "simplex.h"


float simplexNoise2( const float octaves, const float persistence, const float scale, const float x, const float y ) {
  float total = 0;
  float frequency = scale;
  float amplitude = 1;

  float maxAmplitude = 0;

  for( int i=0; i < octaves; i++ ) {
    total += simplexRawNoise2( x * frequency, y * frequency ) * amplitude;

    frequency *= 2;
    maxAmplitude += amplitude;
    amplitude *= persistence;
  }

  return total / maxAmplitude;
}


float simplexNoise3( const float octaves, const float persistence, const float scale, const float x, const float y, const float z ) {
  float total = 0;
  float frequency = scale;
  float amplitude = 1;

  float maxAmplitude = 0;

  for( int i=0; i < octaves; i++ ) {
    total += simplexRawNoise3( x * frequency, y * frequency, z * frequency ) * amplitude;

    frequency *= 2;
    maxAmplitude += amplitude;
    amplitude *= persistence;
  }

  return total / maxAmplitude;
}


float simplexNoise4( const float octaves, const float persistence, const float scale, const float x, const float y, const float z, const float w ) {
  float total = 0;
  float frequency = scale;
  float amplitude = 1;

  float maxAmplitude = 0;

  for( int i=0; i < octaves; i++ ) {
    total += simplexRawNoise4( x * frequency, y * frequency, z * frequency, w * frequency ) * amplitude;

    frequency *= 2;
    maxAmplitude += amplitude;
    amplitude *= persistence;
  }

  return total / maxAmplitude;
}



float simplexScaledNoise2( const float octaves, const float persistence, const float scale, const float loBound, const float hiBound, const float x, const float y ) {
  return simplexNoise2(octaves, persistence, scale, x, y) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}


float simplexScaledNoise3( const float octaves, const float persistence, const float scale, const float loBound, const float hiBound, const float x, const float y, const float z ) {
  return simplexNoise3(octaves, persistence, scale, x, y, z) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}

float simplexScaledNoise4( const float octaves, const float persistence, const float scale, const float loBound, const float hiBound, const float x, const float y, const float z, const float w ) {
  return simplexNoise4(octaves, persistence, scale, x, y, z, w) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}



float simplexScaledRawNoise2( const float loBound, const float hiBound, const float x, const float y ) {
  return simplexRawNoise2(x, y) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}


float simplexScaledRawNoise3( const float loBound, const float hiBound, const float x, const float y, const float z ) {
  return simplexRawNoise3(x, y, z) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}

float simplexScaledRawNoise4( const float loBound, const float hiBound, const float x, const float y, const float z, const float w ) {
  return simplexRawNoise4(x, y, z, w) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}



float simplexRawNoise2( const float x, const float y ) {
  float n0, n1, n2;

  float F2 = 0.5 * (sqrtf(3.0) - 1.0);
  float s = (x + y) * F2;
  int i = fastfloor( x + s );
  int j = fastfloor( y + s );

  float G2 = (3.0 - sqrtf(3.0)) / 6.0;
  float t = (i + j) * G2;
  float X0 = i-t;
  float Y0 = j-t;
  float x0 = x-X0;
  float y0 = y-Y0;

  int i1, j1;
  if(x0>y0) {i1=1; j1=0;}
  else {i1=0; j1=1;}

  float x1 = x0 - i1 + G2;
  float y1 = y0 - j1 + G2;
  float x2 = x0 - 1.0 + 2.0 * G2;
  float y2 = y0 - 1.0 + 2.0 * G2;

  int ii = i & 255;
  int jj = j & 255;
  int gi0 = perm[ii+perm[jj]] % 12;
  int gi1 = perm[ii+i1+perm[jj+j1]] % 12;
  int gi2 = perm[ii+1+perm[jj+1]] % 12;

  float t0 = 0.5 - x0*x0-y0*y0;
  if(t0<0) n0 = 0.0;
  else {
  t0 *= t0;
  n0 = t0 * t0 * dot2(grad3[gi0], x0, y0);
  }

  float t1 = 0.5 - x1*x1-y1*y1;
  if(t1<0) n1 = 0.0;
  else {
  t1 *= t1;
  n1 = t1 * t1 * dot2(grad3[gi1], x1, y1);
  }

  float t2 = 0.5 - x2*x2-y2*y2;
  if(t2<0) n2 = 0.0;
  else {
  t2 *= t2;
  n2 = t2 * t2 * dot2(grad3[gi2], x2, y2);
  }

  return 70.0 * (n0 + n1 + n2);
}


float simplexRawNoise3( const float x, const float y, const float z ) {
  float n0, n1, n2, n3;

  float F3 = 1.0/3.0;
  float s = (x+y+z)*F3;
  int i = fastfloor(x+s);
  int j = fastfloor(y+s);
  int k = fastfloor(z+s);

  float G3 = 1.0/6.0;
  float t = (i+j+k)*G3;
  float X0 = i-t;
  float Y0 = j-t;
  float Z0 = k-t;
  float x0 = x-X0;
  float y0 = y-Y0;
  float z0 = z-Z0;

  int i1, j1, k1;
  int i2, j2, k2;

  if(x0>=y0) {
  if(y0>=z0)
  { i1=1; j1=0; k1=0; i2=1; j2=1; k2=0; }
  else if(x0>=z0) { i1=1; j1=0; k1=0; i2=1; j2=0; k2=1; }
  else { i1=0; j1=0; k1=1; i2=1; j2=0; k2=1; }
  }
  else {
  if(y0<z0) { i1=0; j1=0; k1=1; i2=0; j2=1; k2=1; }
  else if(x0<z0) { i1=0; j1=1; k1=0; i2=0; j2=1; k2=1; }
  else { i1=0; j1=1; k1=0; i2=1; j2=1; k2=0; }
  }

  float x1 = x0 - i1 + G3;
  float y1 = y0 - j1 + G3;
  float z1 = z0 - k1 + G3;
  float x2 = x0 - i2 + 2.0*G3;
  float y2 = y0 - j2 + 2.0*G3;
  float z2 = z0 - k2 + 2.0*G3;
  float x3 = x0 - 1.0 + 3.0*G3;
  float y3 = y0 - 1.0 + 3.0*G3;
  float z3 = z0 - 1.0 + 3.0*G3;

  int ii = i & 255;
  int jj = j & 255;
  int kk = k & 255;
  int gi0 = perm[ii+perm[jj+perm[kk]]] % 12;
  int gi1 = perm[ii+i1+perm[jj+j1+perm[kk+k1]]] % 12;
  int gi2 = perm[ii+i2+perm[jj+j2+perm[kk+k2]]] % 12;
  int gi3 = perm[ii+1+perm[jj+1+perm[kk+1]]] % 12;

  float t0 = 0.6 - x0*x0 - y0*y0 - z0*z0;
  if(t0<0) n0 = 0.0;
  else {
  t0 *= t0;
  n0 = t0 * t0 * dot3(grad3[gi0], x0, y0, z0);
  }

  float t1 = 0.6 - x1*x1 - y1*y1 - z1*z1;
  if(t1<0) n1 = 0.0;
  else {
  t1 *= t1;
  n1 = t1 * t1 * dot3(grad3[gi1], x1, y1, z1);
  }

  float t2 = 0.6 - x2*x2 - y2*y2 - z2*z2;
  if(t2<0) n2 = 0.0;
  else {
  t2 *= t2;
  n2 = t2 * t2 * dot3(grad3[gi2], x2, y2, z2);
  }

  float t3 = 0.6 - x3*x3 - y3*y3 - z3*z3;
  if(t3<0) n3 = 0.0;
  else {
  t3 *= t3;
  n3 = t3 * t3 * dot3(grad3[gi3], x3, y3, z3);
  }

  return 32.0*(n0 + n1 + n2 + n3);
}


float simplexRawNoise4( const float x, const float y, const float z, const float w ) {
  float F4 = (sqrtf(5.0)-1.0)/4.0;
  float G4 = (5.0-sqrtf(5.0))/20.0;
  float n0, n1, n2, n3, n4;

  float s = (x + y + z + w) * F4;
  int i = fastfloor(x + s);
  int j = fastfloor(y + s);
  int k = fastfloor(z + s);
  int l = fastfloor(w + s);
  float t = (i + j + k + l) * G4;
  float X0 = i - t;
  float Y0 = j - t;
  float Z0 = k - t;
  float W0 = l - t;

  float x0 = x - X0;
  float y0 = y - Y0;
  float z0 = z - Z0;
  float w0 = w - W0;

  int c1 = (x0 > y0) ? 32 : 0;
  int c2 = (x0 > z0) ? 16 : 0;
  int c3 = (y0 > z0) ? 8 : 0;
  int c4 = (x0 > w0) ? 4 : 0;
  int c5 = (y0 > w0) ? 2 : 0;
  int c6 = (z0 > w0) ? 1 : 0;
  int c = c1 + c2 + c3 + c4 + c5 + c6;

  int i1, j1, k1, l1;
  int i2, j2, k2, l2;
  int i3, j3, k3, l3;

  i1 = simplex[c][0]>=3 ? 1 : 0;
  j1 = simplex[c][1]>=3 ? 1 : 0;
  k1 = simplex[c][2]>=3 ? 1 : 0;
  l1 = simplex[c][3]>=3 ? 1 : 0;
  i2 = simplex[c][0]>=2 ? 1 : 0;
  j2 = simplex[c][1]>=2 ? 1 : 0;
  k2 = simplex[c][2]>=2 ? 1 : 0;
  l2 = simplex[c][3]>=2 ? 1 : 0;
  i3 = simplex[c][0]>=1 ? 1 : 0;
  j3 = simplex[c][1]>=1 ? 1 : 0;
  k3 = simplex[c][2]>=1 ? 1 : 0;
  l3 = simplex[c][3]>=1 ? 1 : 0;

  float x1 = x0 - i1 + G4;
  float y1 = y0 - j1 + G4;
  float z1 = z0 - k1 + G4;
  float w1 = w0 - l1 + G4;
  float x2 = x0 - i2 + 2.0*G4;
  float y2 = y0 - j2 + 2.0*G4;
  float z2 = z0 - k2 + 2.0*G4;
  float w2 = w0 - l2 + 2.0*G4;
  float x3 = x0 - i3 + 3.0*G4;
  float y3 = y0 - j3 + 3.0*G4;
  float z3 = z0 - k3 + 3.0*G4;
  float w3 = w0 - l3 + 3.0*G4;
  float x4 = x0 - 1.0 + 4.0*G4;
  float y4 = y0 - 1.0 + 4.0*G4;
  float z4 = z0 - 1.0 + 4.0*G4;
  float w4 = w0 - 1.0 + 4.0*G4;

  int ii = i & 255;
  int jj = j & 255;
  int kk = k & 255;
  int ll = l & 255;
  int gi0 = perm[ii+perm[jj+perm[kk+perm[ll]]]] % 32;
  int gi1 = perm[ii+i1+perm[jj+j1+perm[kk+k1+perm[ll+l1]]]] % 32;
  int gi2 = perm[ii+i2+perm[jj+j2+perm[kk+k2+perm[ll+l2]]]] % 32;
  int gi3 = perm[ii+i3+perm[jj+j3+perm[kk+k3+perm[ll+l3]]]] % 32;
  int gi4 = perm[ii+1+perm[jj+1+perm[kk+1+perm[ll+1]]]] % 32;

  float t0 = 0.6 - x0*x0 - y0*y0 - z0*z0 - w0*w0;
  if(t0<0) n0 = 0.0;
  else {
  t0 *= t0;
  n0 = t0 * t0 * dot4(grad4[gi0], x0, y0, z0, w0);
  }

  float t1 = 0.6 - x1*x1 - y1*y1 - z1*z1 - w1*w1;
  if(t1<0) n1 = 0.0;
  else {
  t1 *= t1;
  n1 = t1 * t1 * dot4(grad4[gi1], x1, y1, z1, w1);
  }

  float t2 = 0.6 - x2*x2 - y2*y2 - z2*z2 - w2*w2;
  if(t2<0) n2 = 0.0;
  else {
  t2 *= t2;
  n2 = t2 * t2 * dot4(grad4[gi2], x2, y2, z2, w2);
  }

  float t3 = 0.6 - x3*x3 - y3*y3 - z3*z3 - w3*w3;
  if(t3<0) n3 = 0.0;
  else {
  t3 *= t3;
  n3 = t3 * t3 * dot4(grad4[gi3], x3, y3, z3, w3);
  }

  float t4 = 0.6 - x4*x4 - y4*y4 - z4*z4 - w4*w4;
  if(t4<0) n4 = 0.0;
  else {
  t4 *= t4;
  n4 = t4 * t4 * dot4(grad4[gi4], x4, y4, z4, w4);
  }

  return 27.0 * (n0 + n1 + n2 + n3 + n4);
}


int fastfloor( const float x ) { return x > 0 ? (int) x : (int) x - 1; }

float dot2( const int* g, const float x, const float y ) { return g[0]*x + g[1]*y; }
float dot3( const int* g, const float x, const float y, const float z ) { return g[0]*x + g[1]*y + g[2]*z; }
float dot4( const int* g, const float x, const float y, const float z, const float w ) { return g[0]*x + g[1]*y + g[2]*z + g[3]*w; }

