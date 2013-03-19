/*
 * transformCamera.h
 *
 *  Created on: 26-Sep-2011
 *      Author: apurv
 */

#ifndef TRANSFORMCAMERA_H_
#define TRANSFORMCAMERA_H_

void myGluLookAt(float eyeX,float eyeY,float eyeZ,
			     float centerX,float centerY,float centerZ,
			     float upX,float upY,float upZ);

void myGluLookAtUVW();

void rotateU(float angle);
void rotateV(float angle);
void rotateW(float angle);

#endif /* TRANSFORMCAMERA_H_ */
