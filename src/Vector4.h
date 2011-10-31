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

	double getX(){return getI(0);}
	double getY(){return getI(1);}
	double getZ(){return getI(2);}
	double getW(){return getI(3);}

	double getI(int i);
	void setI(int i, double value);

	void DisplayVector4();
	void SetVector4(double x, double y, double z, double w);
	void Homogenize();
	Vector4* Add(Vector4& a, Vector4& b);
	Vector4* Subtract(Vector4& a, Vector4& b);

	Vector4* CrossProduct(Vector4 &a, Vector4 &b);
	double DotProduct(Vector4 &a, Vector4 &b);

	void ConvertToUnit();
	void Elongate(double factor);
	void GetCopyOf(Vector4 &a);
	double GetMagnitude();

private:
	double **v;

};

#endif /* VECTOR4_H_ */
