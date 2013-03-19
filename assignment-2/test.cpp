/*
 * test.cpp
 *
 *  Created on: 26-Sep-2011
 *      Author: apurv
 */

#include "test.h"
#include "Matrix4.h"
#include "Vector4.h"

void testVector(){
	Vector4 a;
	Vector4 b;
	a.SetVector4(1,0,0,1);
	b.SetVector4(2,0,0,2);
	Vector4* c;
	c = a.Add(b,a);
	c->DisplayVector4();

	delete c;
}

void testMatrix(){
	Matrix4 m1;
	Matrix4 m2;
	m1.SetMatrix4(1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1);
	m2.SetMatrix4(1,-1,2,1,  2,1,2,1,  -2,-2,1,1,  1,1,1,1);
	Matrix4* ans = m1.MultiplyByMatrix(m1,m2);
	ans->DisplayMatrix4();

	ans->SetMatrix4(1,-1,3,0,  2,1,2,0,  -2,-2,1,0,  0,0,0,1);
	//ans->SetMatrix4(2,0,0,0, 0,2,0,0, 0,0,2,0, 0,0,0,2);
	Matrix4* inv = m1.FindInverse(*ans);
	delete ans;

	inv->DisplayMatrix4();
	delete inv;
}


void testCrossProduct(){
	Vector4 a;
	Vector4 b;
	a.SetVector4(1,2,0,1);
	b.SetVector4(2,1,1,1);
	Vector4* c;
	c = a.CrossProduct(b,a);
	c->DisplayVector4();

	delete c;
}

void testMultiplyByMatrix(){
	Matrix4 m1;
	Matrix4 m2;

	m1.SetMatrix4(1,0,0,0.05,  0,1,0,0,  0,0,1,0,  0,0,0,1);
	m2.SetMatrix4(1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1);

	Matrix4* ans = m2.MultiplyByMatrix(m1,m2);
	ans->DisplayMatrix4();
}


void Test(){
	//testVector();
	//testMatrix();
	//testCrossProduct();
	testMultiplyByMatrix();
}


