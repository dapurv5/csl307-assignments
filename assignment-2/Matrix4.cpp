/*
 * Matrix4.cpp
 *
 *  Created on: 22-Sep-2011
 *      Author: apurv
 */

#include "Matrix4.h"
#include <iostream>

using namespace std;


#define R 4
#define C 4

Matrix4::Matrix4() {
	v = new float *[R];
	int i=0;

	for(i = 0; i < R; i++){
		v[i] = new float[C];
	}
	this->SetMatrix4(0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1);
}

Matrix4::~Matrix4() {
	int i =0;
	for(i = 0; i < R; i++){
		delete [] v[i];
	}
	delete [] v;
}


void Matrix4::SetMatrix4(float x00, float x01, float x02, float x03,
				         float x10, float x11, float x12, float x13,
						 float x20, float x21, float x22, float x23,
						 float x30, float x31, float x32, float x33){
	this->v[0][0] = x00;
	this->v[0][1] = x01;
	this->v[0][2] = x02;
	this->v[0][3] = x03;

	this->v[1][0] = x10;
	this->v[1][1] = x11;
	this->v[1][2] = x12;
	this->v[1][3] = x13;

	this->v[2][0] = x20;
	this->v[2][1] = x21;
	this->v[2][2] = x22;
	this->v[2][3] = x23;

	this->v[3][0] = x30;
	this->v[3][1] = x31;
	this->v[3][2] = x32;
	this->v[3][3] = x33;
}


/**
 *
 */
void Matrix4::DisplayMatrix4(){
	int i = 0;
	int j = 0;
	cout<< "[ ";
	for(i = 0; i < R; i++){
		cout << "[ ";
		for(j = 0; j < C; j++){
			if(j == C-1)
				cout << v[i][j] <<", ], ";
			else
				cout << v[i][j] << ", ";
		}
	}
	cout<< "]"<< endl;
}

/**
 *
 * @param a
 * @param b
 * @return
 */
Matrix4* Matrix4::Add(Matrix4 &a, Matrix4 &b){
	Matrix4* c = new Matrix4();

	int i = 0;
	int j = 0;
	for(i = 0; i < R; i++){
		for(j = 0; j < C; j++){
			c->v[i][j] = a.v[i][j] + b.v[i][j];
		}
	}

	return c;
}

/**
 *
 * @param a
 * @param b
 * @return
 */
Matrix4* Matrix4::Subtract(Matrix4 &a, Matrix4 &b){
	Matrix4* c = new Matrix4();

	int i = 0;
	int j = 0;
	for(i = 0; i < R; i++){
		for(j = 0; j < C; j++){
			c->v[i][j] = a.v[i][j] - b.v[i][j];
		}
	}

	return c;
}

/**
 *
 * @param a
 * @param k
 * @return
 */
Matrix4* Matrix4::MultiplyByScalar(Matrix4 &a, float k){
	Matrix4* c = new Matrix4();
	int i = 0;
	int j = 0;
	for(i = 0; i < R; i++){
		for(j = 0; j < C; j++){
			c->v[i][j] = a.v[i][j]*k;
		}
	}
	return c;
}

/**
 * Assuming that number of columns in a vector is 1 and the number of rows in the
 * vector is the same as the number of rows in the matrix.
 * @param a
 * @param b
 * @return
 */
Vector4* Matrix4::MultiplyByVector(Matrix4 &a, Vector4 &b){
	Vector4* c = new Vector4();

	int i = 0;
	int j = 0;
	float sum = 0;
	for( i = 0; i < R; i++){
		sum = 0;
		for(j = 0; j < C; j++){
			sum+= a.v[i][j]*b.getI(j);
		}
		c->setI(i,sum);

	}
	return c;
}

Matrix4* Matrix4::MultiplyByMatrix(Matrix4 &a, Matrix4 &b){
	Matrix4* c = new Matrix4();
	int i = 0;
	int j = 0;

	c->SetMatrix4(0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0);

	for(i = 0; i < R; i++){

		for(j = 0; j < C; j++){
			for(int k = 0; k < C; k++){
				c->v[i][j]+=a.v[i][k]*b.v[k][j];
			}
		}
	}
	return c;
}

Matrix4* Matrix4::Transpose(Matrix4 &a){
	Matrix4* c = new Matrix4();
	int i = 0;
	int j = 0;
	for(i = 0; i < R; i++){
		for(j = 0; j<C; j++){
			c->v[j][i] = a.v[i][j];
		}
	}
	return c;
}

/**
 * Calculates inverse Gauss Jordan Elimination method.
 * @param a
 * @return NULL if the matrix is not invertible.
 */
Matrix4* Matrix4::FindInverse(Matrix4 &a){

	int n = R;
	int i = 0;
	int j = 0;
	float pivot = 0;
	Matrix4* invA = NULL;
	//TODO: Check whether the matrix is invertible.Else Return
	invA = new Matrix4();
	invA->SetMatrix4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);


	for(i = 0; i < n; i++){
		pivot = a.v[i][i];

		if(pivot != 1.0 and pivot != 0){
			for(int t = i; t < n; t++){
				a.v[i][t] = a.v[i][t]/pivot;
				invA->v[i][t] = invA->v[i][t]/pivot;
			}
		}

		//Update to the new pivot which must be 1.0
		pivot = a.v[i][i];

		for(j = 0; j < n; j++){
			if( j==i ){
				continue;

			}
			else{
				float l = a.v[j][i]/pivot;
				for(int m = 0; m < n; m++){
					a.v[j][m] = a.v[j][m] - l * a.v[i][m];
					invA->v[j][m] = invA->v[j][m] - (l * invA->v[i][m]);
				}
			}
		}
	}
	return invA;
}

/**
 * Copies a into this matrix.
 * @param a
 */
void Matrix4::GetCopyOf(Matrix4* a){
	int r = 4;
	int c = 4;
	int i = 0;
	int j = 0;
	for(i = 0; i<r; i++){
		for(j = 0; j<c; j++){
			this->v[i][j] = a->getV(i,j);
		}
	}
}

/**
 * Returns v[i][j] element of this array.
 * @param i
 * @param j
 * @return
 */
float Matrix4::getV(int i, int j){
	float value = this->v[i][j];
	return value;
}
