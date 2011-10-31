/*
 * test.cpp
 *
 *  Created on: 26-Oct-2011
 *      Author: apurv
 */

#include "../Ray.h";
#include <auto_ptr.h>
#include "../geometryKernel.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

void test_ray(){

	auto_ptr<Ray> ray(new Ray(0,0,0,1,2,2));
	ray->printRay();
}


void test_findNormalToTriangle(){

	Triangle triangle;

	triangle.v[0].position[0] = 2.0;
	triangle.v[0].position[1] = 0;
	triangle.v[0].position[2] = 0;
	triangle.v[0].normal[0] = 0;
	triangle.v[0].normal[1] = 0;
	triangle.v[0].normal[2] = 1.0;

	triangle.v[1].position[0] = -2.0;
	triangle.v[1].position[1] = 0;
	triangle.v[1].position[2] = 0;
	triangle.v[1].normal[0] = 0;
	triangle.v[1].normal[1] = 0;
	triangle.v[1].normal[2] = 1.0;


	triangle.v[2].position[0] = 0;
	triangle.v[2].position[1] = 2.0;
	triangle.v[2].position[2] = 0;
	triangle.v[2].normal[0] = 0;
	triangle.v[2].normal[1] = 0;
	triangle.v[2].normal[2] = 1.0;


	cout << "Finding the normal \n";
	auto_ptr<Vector4> normal(findNormalToTriangle(0,1,0, triangle));
	normal->DisplayVector4();

	return;

}

void test_findReflectedRayDirection(){

	cout<<"Finding the reflected ray.";
	Vector4* N = new Vector4();
	N->SetVector4(0,1,0,1);

	Vector4* L = new Vector4();
	//L->SetVector4(-1,1,0,1);
	L->SetVector4(0,1,0,1);

	Vector4* R = findReflectedRayDirection(*N, *L);
	R->DisplayVector4();

	delete R;
}




void Test(){
	//test_ray();
	//test_findNormalToTriangle();
	//test_findReflectedRayDirection();
	//exit(0);
}
