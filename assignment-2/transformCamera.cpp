/*
 * transformCamera.cpp
 *
 *  Created on: 26-Sep-2011
 *      Author: apurv
 */

#include "transformWorld.h"
#include "transformCamera.h"
#include "Vector4.h"
#include "Matrix4.h"

#include <iostream>

using namespace std;

extern Matrix4 modelMatrix;
extern Matrix4 viewMatrix;

extern Vector4 uVector;
extern Vector4 vVector;
extern Vector4 wVector;

/**
 * Explicit implementation of the inbuilt gluLookAt() function.
 * @param eyeX
 * @param eyeY
 * @param eyeZ
 * @param centerX
 * @param centerY
 * @param centerZ
 * @param upX
 * @param upY
 * @param upZ
 */
void myGluLookAt(float eyeX,float eyeY,float eyeZ,
			     float centerX,float centerY,float centerZ,
			     float upX,float upY,float upZ){

	//Remember this W vector is opposite to what is given in the slides.
	//Here W is in the direction of look vector.

	Vector4 W;
	Vector4 U;
	Vector4 V;
	Vector4* temp;

	Vector4 UP;
	UP.SetVector4(upX, upY, upZ,1);
	UP.ConvertToUnit();

	W.SetVector4(centerX-eyeX, centerY-eyeY, centerZ-eyeZ,1);
	W.ConvertToUnit();
	W.Elongate(-1.0); //Now W is in the same direction as the slides.

	temp = U.CrossProduct(UP,W);
	U.SetVector4(temp->getX(), temp->getY(), temp->getZ(), 1);
	U.ConvertToUnit();
	delete temp;

	temp = V.CrossProduct(W,U);
	V.SetVector4(temp->getX(), temp->getY(), temp->getZ(), 1);
	V.ConvertToUnit();
	delete temp;

	float u_x = U.getX();
	float u_y = U.getY();
	float u_z = U.getZ();

	float v_x = V.getX();
	float v_y = V.getY();
	float v_z = V.getZ();

	float w_x = W.getX();
	float w_y = W.getY();
	float w_z = W.getZ();

	Matrix4 initialViewMatrix;
	initialViewMatrix.GetCopyOf(&viewMatrix);

	viewMatrix.SetMatrix4(u_x,u_y,u_z,-1.0*eyeX, v_x,v_y,v_z,-1.0*eyeY, w_x,w_y,w_z,-1.0*eyeZ, 0,0,0,1);

	Matrix4* product = viewMatrix.MultiplyByMatrix(viewMatrix, initialViewMatrix);
	viewMatrix.GetCopyOf(product);

	//Update the global uVector, vVector and wVector.
	uVector.SetVector4(U.getX(), U.getY(), U.getZ(),1);
	vVector.SetVector4(V.getX(), V.getY(), V.getZ(),1);
	wVector.SetVector4(W.getX(), W.getY(), W.getZ(),1);

	delete product;
}


/**
 * Another version of glu look at which instead takes u,v and w vectors to compute the view matrix.
 * @param u
 * @param v
 * @param w
 */
void myGluLookAtUVW(){
	float u_x = uVector.getX();
	float u_y = uVector.getY();
	float u_z = uVector.getZ();

	float v_x = vVector.getX();
	float v_y = vVector.getY();
	float v_z = vVector.getZ();

	float w_x = wVector.getX();
	float w_y = wVector.getY();
	float w_z = wVector.getZ();

	Matrix4 tempMatrix;

	//tempMatrix.SetMatrix4(u_x,u_y,u_z,0, v_x,v_y,v_z,0, w_x,w_y,w_z,0, 0,0,0,1);
	viewMatrix.SetMatrix4(u_x,u_y,u_z,0, v_x,v_y,v_z,0, w_x,w_y,w_z,0, 0,0,0,1);


	//Matrix4* product = viewMatrix.MultiplyByMatrix(tempMatrix, viewMatrix);
	//viewMatrix.GetCopyOf(product);

	//delete product;
}


void rotateU(float angle){
	float x2 = uVector.getX();
	float y2 = uVector.getY();
	float z2 = uVector.getZ();

	Matrix4* rot = giveRotateAboutAxisMatrix(0,0,0, x2,y2,z2, -1.0*angle);

	Vector4* newVVector;
	Vector4* newWVector;

	newVVector = rot->MultiplyByVector(*rot, vVector);
	vVector.GetCopyOf(*newVVector);

	newWVector = rot->MultiplyByVector(*rot, wVector);
	wVector.GetCopyOf(*newWVector);

	myGluLookAtUVW();

	delete rot;
	delete newVVector;
	delete newWVector;
}


void rotateV(float angle){
	float x2 = vVector.getX();
	float y2 = vVector.getY();
	float z2 = vVector.getZ();

	Matrix4* rot = giveRotateAboutAxisMatrix(0,0,0, x2,y2,z2, -1.0*angle);

	Vector4* newUVector;
	Vector4* newWVector;

	newUVector = rot->MultiplyByVector(*rot, uVector);
	uVector.GetCopyOf(*newUVector);

	newWVector = rot->MultiplyByVector(*rot, wVector);
	wVector.GetCopyOf(*newWVector);

	myGluLookAtUVW();

	delete rot;
	delete newUVector;
	delete newWVector;
}



void rotateW(float angle){

	float x2 = wVector.getX();
	float y2 = wVector.getY();
	float z2 = wVector.getZ();

	//TODO: Change this
	Matrix4* rot = giveRotateAboutAxisMatrix(0,0,0, x2,y2,z2, -1.0*angle);

	Vector4* newVVector;
	Vector4* newUVector;

	newVVector = rot->MultiplyByVector(*rot, vVector);
	vVector.GetCopyOf(*newVVector);

	newUVector = rot->MultiplyByVector(*rot, uVector);
	uVector.GetCopyOf(*newUVector);

	myGluLookAtUVW();

	delete rot;
	delete newVVector;
	delete newUVector;
}
