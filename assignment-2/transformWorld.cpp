/*
 * transform.cpp
 *
 *  Created on: 24-Sep-2011
 *      Author: apurv
 */
#include "transformWorld.h"
#include "Matrix4.h"
#include "Vector4.h"

#include <math.h>
#include <iostream>

//Contains necessary functions for doing transformations.

extern Matrix4 modelMatrix;

using namespace std;


/**
 * Translates all the points in the data structure by value distance along the positive x direction.
 * For translating along negative x axis, use negative distance.
 * @param distanceTranslate
 */
void translateX(float distance){
	Matrix4 m;
	m.SetMatrix4(1,0,0,distance, 0,1,0,0, 0,0,1,0, 0,0,0,1);

    //Now modify the model matrix;
    Matrix4* resu = m.MultiplyByMatrix(m, modelMatrix);

    modelMatrix.GetCopyOf(resu); //Copy the result into modelMatrix
    delete resu;
}



/**
 * Translates all the points in the data structure by value distance along the positive y direction.
 * For translating along negative y axis, use negative distance.
 * @param distance
 */
void translateY(float distance){
	Matrix4 m;
	m.SetMatrix4(1,0,0,0, 0,1,0,distance, 0,0,1,0, 0,0,0,1);

    //Now modify the model matrix;
    Matrix4* resu = m.MultiplyByMatrix(m, modelMatrix);

    modelMatrix.GetCopyOf(resu); //Copy the result into modelMatrix
    delete resu;
}



/**
 * Translates all the points in the data structure by value distance along the positive z direction.
 * For translating along negative z axis, use negative distance.
 * @param distance
 */
void translateZ(float distance){
	Matrix4 m;
	m.SetMatrix4(1,0,0,0, 0,1,0,0, 0,0,1,distance, 0,0,0,1);

    //Now modify the model matrix;
    Matrix4* resu = m.MultiplyByMatrix(m, modelMatrix);

    modelMatrix.GetCopyOf(resu); //Copy the result into modelMatrix
    delete resu;
}



/**
 * Rotates all the points in the data structure by value = angle about the x axis in anti-clockwise sense.
 * @param angle
 */
void rotateX(float angle){
	Matrix4 m;
	m.SetMatrix4(1,0,0,0, 0,cos(angle),-1.0*sin(angle),0, 0,sin(angle),cos(angle),0, 0,0,0,1);

    //Now modify the model matrix;
    Matrix4* resu = m.MultiplyByMatrix(m, modelMatrix);

    modelMatrix.GetCopyOf(resu); //Copy the result into modelMatrix
    delete resu;
}

/**
 * Rotates all the points in the data structure by value = angle, about the y axis in anti-clockwise sense.
 * @param angle
 */
void rotateY(float angle){
	Matrix4 m;
	m.SetMatrix4(cos(angle),0,sin(angle),0, 0,1,0,0, -1.0*sin(angle),0,cos(angle),0, 0,0,0,1);

    //Now modify the model matrix;
    Matrix4* resu = m.MultiplyByMatrix(m, modelMatrix);

    modelMatrix.GetCopyOf(resu); //Copy the result into modelMatrix
    delete resu;
}

/**
 * Rotates all the points in the data structure by value = angle, about the z axis in anti-clockwise sense.
 * @param angle
 */
void rotateZ(float angle){
	Matrix4 m;
	m.SetMatrix4(cos(angle),-1.0*sin(angle),0,0, sin(angle),cos(angle),0,0, 0,0,1,0, 0,0,0,1);

    //Now modify the model matrix;
    Matrix4* resu = m.MultiplyByMatrix(m, modelMatrix);

    modelMatrix.GetCopyOf(resu); //Copy the result into modelMatrix
    delete resu;
}


/**
 * Scales the object by the specified factor along the x axis.
 * @param factor
 */
void scaleX(float factor){
	Matrix4 m;
	m.SetMatrix4(factor,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);

    //Now modify the model matrix;
    Matrix4* resu = m.MultiplyByMatrix(m, modelMatrix);

    modelMatrix.GetCopyOf(resu); //Copy the result into modelMatrix
    delete resu;
}


/**
 * Scales the object by the specified factor along the y axis.
 * @param factor
 */
void scaleY(float factor){
	Matrix4 m;
	m.SetMatrix4(1,0,0,0, 0,factor,0,0, 0,0,1,0, 0,0,0,1);

    //Now modify the model matrix;
    Matrix4* resu = m.MultiplyByMatrix(m, modelMatrix);

    modelMatrix.GetCopyOf(resu); //Copy the result into modelMatrix
    delete resu;
}


/**
 * Scales the object by the specified factor along the z axis.
 * @param factor
 */
void scaleZ(float factor){
	Matrix4 m;
	m.SetMatrix4(1,0,0,0, 0,1,0,0, 0,0,factor,0, 0,0,0,1);

    //Now modify the model matrix;
    Matrix4* resu = m.MultiplyByMatrix(m, modelMatrix);

    modelMatrix.GetCopyOf(resu); //Copy the result into modelMatrix
    delete resu;
}

/**
 * Rotates the points in the world coordinate system about the specified axis.
 * @param x1
 * @param y1
 * @param z1
 * @param x2
 * @param y2
 * @param z2
 */
void rotateAboutAxis(float x1, float y1, float z1, float x2, float y2, float z2, float theta){
	translateX(-1.0*x1);
	translateY(-1.0*y1);
	translateZ(-1.0*z1);
	rotateX(atan2(y2-y1,z2-z1));
	rotateY(atan2(x2-x1,z2-z1));

	rotateZ(theta);

	rotateY(-1.0*atan2(x2-x1,z2-z1));
	rotateX(-1.0*atan2(y2-y1,z2-z1));
	translateZ(z1);
	translateY(y1);
	translateX(x1);
}




Matrix4* giveRotateAboutAxisMatrix(float x1, float y1, float z1, float x2, float y2, float z2, float theta){

	Matrix4* m = new Matrix4();
	m->SetMatrix4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);

	applyTranslateXYZMatrix(-1.0*x1, -1.0*y1, -1.0*z1, *m);

	applyRotateXMatrix(atan2(y2-y1,z2-z1), *m);
	applyRotateYMatrix(atan2(x2-x1,z2-z1), *m);

	applyRotateZMatrix(theta, *m);

	applyRotateYMatrix(-1.0*atan2(x2-x1,z2-z1), *m);
	applyRotateXMatrix(-1.0*atan2(y2-y1,z2-z1), *m);

	applyTranslateXYZMatrix(x1, y1, z1, *m);
	return m;
}


/**
 * Returns translate(x,y,z) matrix * tXYZ.
 * @param x
 * @param y
 * @param z
 */
void applyTranslateXYZMatrix(float x, float y, float z, Matrix4& matrix){

	Matrix4 tXYZ;
	tXYZ.SetMatrix4(1,0,0,x, 0,1,0,y, 0,0,1,z, 0,0,0,1);

	Matrix4* result = tXYZ.MultiplyByMatrix(tXYZ, matrix);
	matrix.GetCopyOf(result);
	delete result;
}


void applyRotateXMatrix(float angle, Matrix4& matrix){

	Matrix4 m;
	m.SetMatrix4(1,0,0,0, 0,cos(angle),-1.0*sin(angle),0, 0,sin(angle),cos(angle),0, 0,0,0,1);

	Matrix4* result = m.MultiplyByMatrix(m, matrix);
	matrix.GetCopyOf(result);
	delete result;
}

void applyRotateYMatrix(float angle, Matrix4& matrix){

	Matrix4 m;
	m.SetMatrix4(cos(angle),0,sin(angle),0, 0,1,0,0, -1.0*sin(angle),0,cos(angle),0, 0,0,0,1);

	Matrix4* result = m.MultiplyByMatrix(m, matrix);
	matrix.GetCopyOf(result);
	delete result;
}

void applyRotateZMatrix(float angle, Matrix4& matrix){

	Matrix4 m;
	m.SetMatrix4(cos(angle),-1.0*sin(angle),0,0, sin(angle),cos(angle),0,0, 0,0,1,0, 0,0,0,1);

	Matrix4* result = m.MultiplyByMatrix(m, matrix);
	matrix.GetCopyOf(result);
	delete result;
}



