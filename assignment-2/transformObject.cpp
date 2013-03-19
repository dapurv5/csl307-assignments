/*
 * transformObject.cpp
 *
 *  Created on: 26-Sep-2011
 *      Author: apurv
 */
#include "Matrix4.h"
#include <math.h>

extern Matrix4 modelMatrix;

/**
 * Rotates the object about its Z axis.
 * @param t
 */
void rotateK(float t){
	Matrix4 m;
	m.SetMatrix4(cos(t),-1.0*sin(t),0,0, sin(t),cos(t),0,0, 0,0,1,0, 0,0,0,1);

    //Now modify the model matrix;
    Matrix4* resu = m.MultiplyByMatrix(modelMatrix, m);

    modelMatrix.GetCopyOf(resu); //Copy the result into modelMatrix
    delete resu;
}

/**
 * Rotates the object about its y axis.
 * @param t
 */
void rotateJ(float t){
	Matrix4 m;
	m.SetMatrix4(cos(t),0,sin(t),0, 0,1,0,0, -1.0*sin(t),0,cos(t),0, 0,0,0,1);

    //Now modify the model matrix;
    Matrix4* resu = m.MultiplyByMatrix(modelMatrix, m);

    modelMatrix.GetCopyOf(resu); //Copy the result into modelMatrix
    delete resu;
}

/**
 * Rotates the object about its x axis.
 * @param t
 */
void rotateI(float t){
	Matrix4 m;
	m.SetMatrix4(1,0,0,0, 0,cos(t),-1.0*sin(t),0, 0,sin(t),cos(t),0, 0,0,0,1);

    //Now modify the model matrix;
    Matrix4* resu = m.MultiplyByMatrix(modelMatrix, m);

    modelMatrix.GetCopyOf(resu); //Copy the result into modelMatrix
    delete resu;
}

/**
 * Scales the object equally along three dimensions.
 * @param factor
 */
void scaleIJK(float factor){
	Matrix4 m;
	m.SetMatrix4(factor,0,0,0, 0,factor,0,0, 0,0,factor,0, 0,0,0,1);

    //Now modify the model matrix;
    Matrix4* resu = m.MultiplyByMatrix(modelMatrix,m);

    modelMatrix.GetCopyOf(resu); //Copy the result into modelMatrix
    delete resu;
}

