/*
 * Ray.h
 *
 *  Created on: 26-Oct-2011
 *      Author: apurv
 */

#ifndef RAY_H_
#define RAY_H_

class Ray {
	double x0;
	double y0;
	double z0;

	double xd;
	double yd;
	double zd;

	void Normalize(void);
public:
	Ray(double x0, double y0, double z0, double x1, double y1, double z1);
	virtual ~Ray();
    double getX0() const;
    double getXd() const;
    double getY0() const;
    double getYd() const;
    double getZ0() const;
    double getZd() const;
    void setX0(double x0);
    void setXd(double xd);
    void setY0(double y0);
    void setYd(double yd);
    void setZ0(double z0);
    void setZd(double zd);
    void printRay(void);


};

#endif /* RAY_H_ */
