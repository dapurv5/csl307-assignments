/*
 * Vector4.h
 *
 *  Created on: 21-Sep-2011
 *      Author: apurv
 */

#ifndef VECTOR4_H_
#define VECTOR4_H_

class Vector4 {

public:
	Vector4();
	virtual ~Vector4();

	float getX(){return getI(0);}
	float getY(){return getI(1);}
	float getZ(){return getI(2);}
	float getW(){return getI(3);}

	float getI(int i);
	void setI(int i, float value);

	void DisplayVector4();
	void SetVector4(float x, float y, float z, float w);
	void Homogenize();
	Vector4* Add(Vector4& a, Vector4& b);
	Vector4* Subtract(Vector4& a, Vector4& b);

	Vector4* CrossProduct(Vector4 &a, Vector4 &b);
	float DotProduct(Vector4 &a, Vector4 &b);

	void ConvertToUnit();
	void Elongate(float factor);
	void GetCopyOf(Vector4 &a);

private:
	float **v;

};

#endif /* VECTOR4_H_ */
