/*
 * colorKernel.cpp
 *
 *  Created on: 27-Oct-2011
 *      Author: apurv
 */

#include "colorKernel.h"
#include "geometryKernel.h"
#include "Vector4.h"
#include "Ray.h"
#include "interpolator.h"

#include <stdlib.h>
#include <iostream>
#include <auto_ptr.h>
#include <math.h>

using namespace std;


extern Triangle triangles[MAX_TRIANGLES];
extern Sphere spheres[MAX_SPHERES];
extern Light lights[MAX_LIGHTS];
extern double ambient_light[3];

extern int iType;
extern int index_sphere;
extern int index_triangle;
extern int num_lights;
extern int num_triangles;
extern int num_spheres;


Color* getColor(double x, double y, double z, double t){

	Color* color = new Color(0,0,0);
	int red = 0;
	int green = 0;
	int blue = 0;

	double ka_red = 0.0;
	double ka_green = 0.0;
	double ka_blue = 0.0;

	double kd_red = 0.0;
	double kd_green = 0.0;
	double kd_blue = 0.0;

	double ks_red = 0.0;
	double ks_green= 0.0;
	double ks_blue = 0.0;

	double shininess = 0.0;

	//The view vector from the point of intersection to where the user is standing.
	Vector4* V = findViewDirection(x,y,z);
	V->ConvertToUnit();

	//The normal vector to the surface obtained by interpolating the normals.
	Vector4* N = new Vector4();
	N->SetVector4(0,0,0,1);

	if(iType == SPHERE){
		N->GetCopyOf( *findNormalToSphere(x,y,z,spheres[index_sphere]) );
		N->ConvertToUnit();

		kd_red = spheres[index_sphere].color_diffuse[0];
		kd_green = spheres[index_sphere].color_diffuse[1];
		kd_blue = spheres[index_sphere].color_diffuse[2];

		ks_red = spheres[index_sphere].color_specular[0];
		ks_green = spheres[index_sphere].color_specular[1];
		ks_blue = spheres[index_sphere].color_specular[2];

		shininess = spheres[index_sphere].shininess;

	}
	if(iType == TRIANGLE){

		N->GetCopyOf( *findNormalToTriangle(x,y,z,triangles[index_triangle]) );
		N->ConvertToUnit();

		Vector4* Kd = interpolateKd(x,y,z, triangles[index_triangle]);
		Vector4* Ks = interpolateKs(x,y,z, triangles[index_triangle]);

		kd_red = Kd->getX();
		kd_green = Kd->getY();
		kd_blue = Kd->getZ();

		ks_red = Ks->getX();
		ks_green =  Ks->getY();
		ks_blue =  Ks->getZ();

		shininess = interpolateShininess(x,y,z, triangles[index_triangle]);

		delete Kd;
		delete Ks;
	}

	ka_red = kd_red;
	ka_green = kd_green;
	ka_blue = kd_blue;

	color->addMoreRed((int)getAmbientRed(ka_red));
	color->addMoreGreen((int)getAmbientGreen(ka_green));
	color->addMoreBlue((int)getAmbientBlue(ka_blue));

	int i =0;
	for(i = 0; i<num_lights; i++){
		//Light Vector (From the point of intersection to the light source)
		auto_ptr<Vector4> L(findLightDirection(x,y,z,lights[i]));
		L->ConvertToUnit();

		//Reflected Ray Vector
		auto_ptr<Vector4> R(findReflectedRayDirection(*N, *L));
		R->ConvertToUnit();

		double LN = L->DotProduct(*L, *N);
		double RV = R->DotProduct(*R, *V);

//		if(isShadowed(x,y,z,lights[i]) and LN>=0){
		if(isShadowed(x,y,z,lights[i])){
			red = 0;
			green = 0;
			blue = 0;

		}else{

			red = getRed(lights[i].color[0], ka_red, kd_red, ks_red, LN, RV, shininess);
			green = getGreen(lights[i].color[1], ka_green, kd_green, ks_green, LN, RV, shininess);
			blue = getBlue(lights[i].color[2], ka_blue, kd_blue, ks_green, LN, RV, shininess);

		}

//		cout << "more Red "<<red<<", ";/////////////////////////////////////////////////////////
//		cout << "more Green "<<green<<", ";
//		cout << "more Blue "<<blue<<endl;

		color->addMoreRed(red);
		color->addMoreGreen(green);
		color->addMoreBlue(blue);
	}

	delete N;
	iType = NONE;
	return color;
}


int getRed(double I, double ka_red, double kd_red, double ks_red, double LN, double RV, double shininess){

	double diffuse_red = getDiffuseRed(I, kd_red, LN);
	double specular_red = getSpecularRed(I, ks_red, LN, RV, shininess);

	int red = (int)(diffuse_red+specular_red);
	return red;
}

int getGreen(double I,double ka_green, double kd_green, double ks_green, double LN, double RV, double shininess){

	double diffuse_green = getDiffuseGreen(I, kd_green, LN);
	double specular_green = getSpecularGreen(I, ks_green, LN, RV, shininess);

	int green = (int)(diffuse_green+specular_green);
	return green;
}


int getBlue(double I, double ka_blue, double kd_blue, double ks_blue, double LN, double RV, double shininess){

	double diffuse_blue = getDiffuseBlue(I, kd_blue, LN);
	double specular_blue = getSpecularBlue(I, ks_blue, LN, RV, shininess);

	int blue = (int)(diffuse_blue+specular_blue);
	return blue;
}


double getAmbientRed(double ka_red){
	double ambient_red = 255.0 * ambient_light[0]*ka_red;
	return ambient_red;
}

double getAmbientGreen(double ka_green){
	double ambient_green = 255.0 * ambient_light[1]*ka_green;
	return ambient_green;
}

double getAmbientBlue(double ka_blue){
	double ambient_blue = 255.0 * ambient_light[2]*ka_blue;
	return ambient_blue;
}

double getDiffuseRed(double I, double kd_red, double LN){
	double diffuse_red = 255.0*I*kd_red*LN;
	if(LN<=0){
		diffuse_red = 0;
	}
	return diffuse_red;
}

double getDiffuseGreen(double I, double kd_green, double LN){
	double diffuse_green = 255.0*I*kd_green*LN;
	if(LN<=0){
		diffuse_green = 0;
	}
	return diffuse_green;
}

double getDiffuseBlue(double I, double kd_blue, double LN){
	double diffuse_blue = 255.0*I*kd_blue*LN;
	if(LN<=0){
		diffuse_blue = 0;
	}
	return diffuse_blue;
}



double getSpecularRed(double I, double ks_red, double LN, double RV, double shininess){
	double specular_red = 255.0*I*ks_red*pow(RV,shininess);
	if(LN<0 || RV<0){
		specular_red=0;
	}
	return specular_red;
}
double getSpecularGreen(double I, double ks_green, double LN, double RV, double shininess){
	double specular_green = 255.0*I*ks_green*pow(RV,shininess);
	if(LN<0 || RV<0){
		specular_green = 0;
	}
	return specular_green;
}
double getSpecularBlue(double I, double ks_blue, double LN, double RV, double shininess){
	double specular_blue = 255.0*I*ks_blue*pow(RV,shininess);
	if(LN<0 || RV<0){
		specular_blue = 0;
	}
	return specular_blue;
}




bool isShadowed(double x, double y, double z, Light& currentLight){
	double light_x = currentLight.position[0];
	double light_y = currentLight.position[1];
	double light_z = currentLight.position[2];
	bool isInShadow = false;

	//Shadow check.
	Ray* ray = new Ray(x,y,z,light_x, light_y, light_z);
	double t_intr = 5000;

	int i = 0;
	for(i = 0; i < num_spheres; i++){
		Sphere s = spheres[i];

		//Avoid self intersection.
		if(iType == SPHERE and i == index_sphere){
			continue;
		}

		t_intr = findIntersectionWithSphere(*ray,s);

		if(t_intr != NO_INTERSECTION){
			isInShadow = true;
			return isInShadow;
		}

//		if(t_intr>0.9999 or t_intr<0.0001){
//			isInShadow = true;
//			break;
//		}
	}

	for(i=0; i < num_triangles; i++){
		Triangle triangle = triangles[i];

		//Avoid self intersection.
		if(iType == TRIANGLE and i == index_triangle){
			continue;
		}


		t_intr = findIntersectionWithTriangle(*ray, triangle);

//		if(iType == TRIANGLE and index_triangle == INDEX and t_intr!=NO_INTERSECTION and t_intr>=0.01){
//			cout<<t_intr<<endl;///////////////////////////////////
//			cout<<"Ray was";
//			ray->printRay();
//			cout<<"Triangle was "<<i<<endl<<endl;
//		}

		if(t_intr !=NO_INTERSECTION){

			if(t_intr > 0.01){

				double x_i = getXIntersect(*ray, t_intr);
				double y_i = getYIntersect(*ray, t_intr);
				double z_i = getZIntersect(*ray, t_intr);

				//This ray is intersecting the scene behind the light.
				if(distance(x,y,z, light_x, light_y, light_z) > distance(x,y,z, x_i, y_i, z_i)){
					isInShadow = true;
					return isInShadow;
				}
			}

		}
	}

	return isInShadow;

}


double distance(double x1, double y1, double z1, double x2, double y2, double z2){
	double x = x2-x1;
	double y = y2-y1;
	double z = z2-z1;
	double dist = sqrt(x*x+y*y+z*z);
	return dist;
}
