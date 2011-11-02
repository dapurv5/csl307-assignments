/*
 * rayTracer.cpp
 *
 *  Created on: 29-Oct-2011
 *      Author: apurv
 */

#include "rayTracer.h"
#include "geometryKernel.h"
#include "colorKernel.h"
#include "Color.h"

#include <auto_ptr.h>
#include <iostream>

using namespace std;

extern int iType;
extern int index_triangle;

Color* traceRay(Ray& ray, int depth){

	double t = findIntersect(ray);
	//Also the iType would also have been set to either sphere or triangle.

	Color* color = NULL;


	if(t == NO_INTERSECTION and (t<0 or t>1)){
		color = new Color(0,0,0);
		color->setRed(254);
		color->setGreen(254);
		color->setBlue(254);

	}else{
		double x_boom = getXIntersect(ray, t);
		double y_boom = getYIntersect(ray, t);
		double z_boom = getZIntersect(ray, t);
		color = getColor(x_boom,y_boom,z_boom,t, depth+1);

	}
	return color;
}
