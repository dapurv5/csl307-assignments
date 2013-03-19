/*
 * Matrix4.h
 *
 *  Created on: 22-Sep-2011
 *      Author: apurv
 */
#include "Vector4.h"

#ifndef MATRIX4_H_
#define MATRIX4_H_

class Matrix4 {
public:
	Matrix4();
	virtual ~Matrix4();
	void DisplayMatrix4();


	void SetMatrix4(float x00, float x01, float x02, float x03,
					   float x10, float x11, float x12, float x13,
					   float x20, float x21, float x22, float x23,
					   float x30, float x31, float x32, float x33);



	Matrix4* Add(Matrix4 &a, Matrix4 &b);
	Matrix4* Subtract(Matrix4 &a, Matrix4 &b);

	Vector4* MultiplyByVector(Matrix4 &a, Vector4 &b);

	Matrix4* MultiplyByScalar(Matrix4 &a,  float k);
	Matrix4* MultiplyByMatrix(Matrix4 &a, Matrix4 &b);

	Matrix4* Transpose(Matrix4 &a);
	Matrix4* FindInverse(Matrix4 &a);

	void GetCopyOf(Matrix4* a);

	float getV(int i, int j);

private:
	float** v;

};

#endif /* MATRIX4_H_ */
