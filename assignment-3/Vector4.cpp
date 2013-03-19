/*
 * Vector4.cpp
 *
 *  Created on: 21-Sep-2011
 *      Author: apurv
 */

#include "Vector4.h"

#include <math.h>
#include <iostream>

using namespace std;

#define ROWS 4
#define COLUMNS 1

/**
 * Constructor to initialize the array. Just creates the space for the array.
 */
Vector4::Vector4() {
	v = new double *[ROWS];
	int i=0;

	for(i = 0; i < ROWS; i++){
		v[i] = new double[COLUMNS];
	}
	v[ROWS-1][COLUMNS-1] = 1;

}

/**
 * Destructor to free the array.
 */
Vector4::~Vector4() {
	//cout << "Deleting \n";////////
	//DisplayVector4();

	int i =0;
	for(i = 0; i < ROWS; i++){
		delete [] v[i];
	}
	delete [] v;
}


/**
 * Returns the 'i'th component of this vector.
 * @param i
 * @return
 */
double Vector4::getI(int i){
	return this->v[i][0];
}

void Vector4::setI(int i, double value){
	this->v[i][0] = value;
}


/**
 * Displays a vector.
 */
void Vector4::DisplayVector4(){
	int i = 0;
	int j = 0;
	cout << "[ ";
	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLUMNS; j++){
			if(i == ROWS-1)
				cout << v[i][j];
			else
				cout << v[i][j] << ", ";
		}
	}
	cout << "]'"<< endl;
}

/**
 * Creates a vector with the specified x, y, z and w components.
 * @param x
 * @param y
 * @param z
 * @param w
 */
void Vector4::SetVector4(double x, double y, double z, double w){
	v[0][0] = x;
	v[1][0] = y;
	v[2][0] = z;
	v[3][0] = w;
}

/**
 * Homogenizes the this vector making w = 1.
 */
void Vector4::Homogenize(){
	if (v[3][0] == 1){
		return;

	}
	else{
		v[0][0] = v[0][0]/v[3][0];
		v[1][0] = v[1][0]/v[3][0];
		v[2][0] = v[2][0]/v[3][0];
		v[3][0] = 1.0f;
	}
}

/**
 * Calculates Vector a + Vector b
 * Works only for 4 by 1 vectors.
 * @param a
 * @param b
 * @return
 */
Vector4* Vector4::Add(Vector4& a, Vector4& b){

	Vector4* c = new Vector4();
	int i = 0;
	for(i = 0; i< ROWS-1; i++){
		c->setI(i, a.getI(i)+b.getI(i));
	}
	return c;
	//TODO need to check that both the vectors are homogenized.
}

/**
 * Calculates Vector a - Vector b
 * Works only for 4 by 1 vectors.
 * @param a
 * @param b
 * @return
 */
Vector4* Vector4::Subtract(Vector4& a, Vector4& b){
	Vector4* c = new Vector4();
	int i = 0;
	for(i = 0; i< ROWS-1; i++){
		c->setI(i, a.getI(i)-b.getI(i));
	}
	return c;
	//TODO need to check that both the vectors are homogenized.
}


/**
 * Converts this vector to a unit vector in the same direction.
 */
void Vector4::ConvertToUnit(){

	double w = this->getW();
	double x = this->getX()/w;
	double y = this->getY()/w;
	double z = this->getZ()/w;
	double magn = sqrt(x*x + y*y + z*z );
	this->SetVector4(x/magn, y/magn, z/magn, 1);
}

/**
 * Finds a cross b.
 * a and b must be in dimension 3 represented as 4 length vector in homogeneous coordinates.
 * @param a
 * @param b
 * @return
 */
Vector4* Vector4::CrossProduct(Vector4 &u, Vector4 &v){

	u.Homogenize();
	v.Homogenize();

	double a1 = u.getX();
	double a2 = u.getY();
	double a3 = u.getZ();

	double b1 = v.getX();
	double b2 = v.getY();
	double b3 = v.getZ();

	double x = a2*b3 - a3*b2;
	double y = a3*b1 - a1*b3;
	double z = a1*b2 - a2*b1;

	Vector4* product = new Vector4();
	product->SetVector4(x,y,z,1);

	return product;
}

/**
 * Computes dot product.
 *
 * @param u
 * @param v
 * @return
 */
double Vector4::DotProduct(Vector4 &u, Vector4 &v){
	u.Homogenize();
	v.Homogenize();

	double product = 0.0;

	double a1 = u.getX();
	double a2 = u.getY();
	double a3 = u.getZ();

	double b1 = v.getX();
	double b2 = v.getY();
	double b3 = v.getZ();

	product = a1*b1 + a2*b2 + a3*b3;
	return product;
}

/**
 * Multiplies the current vector by factor.
 * @param factor
 */
void Vector4::Elongate(double factor){
	this->Homogenize();

	double w = this->getW();
	double x = this->getX()/w * factor;
	double y = this->getY()/w * factor;
	double z = this->getZ()/w * factor;

	this->SetVector4(x,y,z,1);
}


void Vector4::GetCopyOf(Vector4 &a){
	this->SetVector4(a.getX(), a.getY(), a.getZ(), a.getW());
}


/**
 * Returns the magnitude of this vector as a double value.
 * @return
 */
double Vector4::GetMagnitude(){
	double x = this->getX();
	double y = this->getY();
	double z = this->getZ();
	double w = this->getW();
	double magn = sqrt(x*x + y*y + z*z);
	return magn;
}
