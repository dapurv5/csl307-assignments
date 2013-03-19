/*
 * transform.h
 *
 *  Created on: 24-Sep-2011
 *      Author: apurv
 */
#include "Matrix4.h"

#ifndef TRANSFORMWORLD_H_
#define TRANSFORMWORLD_H_

void translateX(float distance);
void translateY(float distance);
void translateZ(float distance);

void rotateX(float angle);
void rotateY(float angle);
void rotateZ(float angle);

void scaleX(float factor);
void scaleY(float factor);
void scaleZ(float factor);

void rotateAboutAxis(float x1, float y1, float z1, float x2, float y2, float z2, float theta);

void applyTranslateXYZMatrix(float x, float y, float z, Matrix4& a);
void applyRotateXYZMatrix(float alpha, float beta, float gamma, Matrix4& a);
void applyRotateXMatrix(float t, Matrix4& a);
void applyRotateYMatrix(float t, Matrix4& a);
void applyRotateZMatrix(float t, Matrix4& a);

Matrix4* giveRotateAboutAxisMatrix(float x1, float y1, float z1, float x2, float y2, float z2, float theta);

#endif /* TRANSFORMWORLD_H_ */
