/*
 * render.cpp
 *
 *  Created on: 24-Sep-2011
 *      Author: apurv
 */

#include "render.h"
#include "ifs.h"
#include "Matrix4.h"

#include "GL/glut.h"

#include <stdio.h>
#include <iostream>

extern IFS_DATA* data;
extern Matrix4 modelMatrix;
extern Matrix4 viewMatrix;

using namespace std;

void renderMesh(){

	TRIANGLE* t = data->triangles;

	unsigned int i = 0;

	for(i = 0; i < data->numTriangles; i++){

		float x1 = t->a->x;
		float y1 = t->a->y;
		float z1 = t->a->z;

		Vector4 p1;
		p1.SetVector4(x1, y1, z1,1);
		getModelTransformedPoint(p1);
		getViewTransformedPoint(p1);

		float w1 = p1.getW();
		x1 = p1.getX()/w1;
		y1 = p1.getY()/w1;
		z1 = p1.getZ()/w1;

		float x2 = t->b->x;
		float y2 = t->b->y;
		float z2 = t->b->z;

		Vector4 p2;
		p2.SetVector4(x2, y2, z2,1);
		getModelTransformedPoint(p2);
		getViewTransformedPoint(p2);

		float w2 = p2.getW();
		x2 = p1.getX()/w2;
		y2 = p1.getY()/w2;
		z2 = p1.getZ()/w2;


		float x3 = t->c->x;
		float y3 = t->c->y;
		float z3 = t->c->z;

		Vector4 p3;
		p3.SetVector4(x3, y3, z3,1);
		getModelTransformedPoint(p3);
		getViewTransformedPoint(p3);

		float w3 = p3.getW();
		x3 = p3.getX()/w3;
		y3 = p3.getY()/w3;
		z3 = p3.getZ()/w3;

		glBegin(GL_LINE_STRIP);

		glColor3f(1, 1, 1);
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y2, z2);
		glVertex3f(x3, y3, z3);

		glEnd();
		glFlush();

		t++;
	}
}


void getModelTransformedPoint(Vector4 &p){
	Vector4* transformedP;
	transformedP = modelMatrix.MultiplyByVector(modelMatrix, p);

	float x = transformedP->getX();
	float y = transformedP->getY();
	float z = transformedP->getZ();
	float w = transformedP->getW();

	p.SetVector4(x,y,z,w);
	p.Homogenize();

	delete transformedP;
}


void getViewTransformedPoint(Vector4 &p){
	Vector4* transformedP;
	transformedP = viewMatrix.MultiplyByVector(viewMatrix, p);

	float x = transformedP->getX();
	float y = transformedP->getY();
	float z = transformedP->getZ();
	float w = transformedP->getW();

	p.SetVector4(x,y,z,w);
	p.Homogenize();

	delete transformedP;
}


