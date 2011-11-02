/*
 * geometry_kernel.h
 *
 *  Created on: 26-Oct-2011
 *      Author: apurv
 */
#include "Ray.h"
#include "Vector4.h"
#include <auto_ptr.h>


#define INDEX 0
#define MAX_DEPTH 2



#define MAX_TRIANGLES 1500
#define MAX_SPHERES 100
#define MAX_LIGHTS 10

#define NO_INTERSECTION -10000


#ifndef GEOMETRY_KERNEL_H_
#define GEOMETRY_KERNEL_H_


enum intersection_type {SPHERE, TRIANGLE, NONE};


struct Vertex
{
  double position[3];
  double color_diffuse[3];
  double color_specular[3];
  double normal[3];
  double shininess;
};

typedef struct _Triangle
{
  struct Vertex v[3];
} Triangle;

typedef struct _Sphere
{
  double position[3];
  double color_diffuse[3];
  double color_specular[3];
  double shininess;
  double radius;
} Sphere;

typedef struct _Light
{
  double position[3];
  double color[3];
} Light;






double findIntersect(Ray& r);
double findIntersectionWithSphere(Ray& r, Sphere& s);
double findIntersectionWithTriangle(Ray& r, Triangle& t);
bool isInsideTheTriangle(Vector4& P0, Vector4& P1, Vector4& P2, Vector4& P, Vector4& n);

double getXIntersect(Ray& r, double t);
double getYIntersect(Ray& r, double t);
double getZIntersect(Ray& r, double t);

Vector4* findLightDirection(double xS, double yS, double zS, Light& light);
Vector4* findNormalToTriangle(double xS, double yS, double zS, Triangle& triangle);
Vector4* findNormalToSphere(double xS, double yS, double zS, Sphere& sphere);
Vector4* findReflectedRayDirection(Vector4& N, Vector4& L);
Vector4* findViewDirection(double xS, double yS, double zS);


#endif /* GEOMETRY_KERNEL_H_ */
