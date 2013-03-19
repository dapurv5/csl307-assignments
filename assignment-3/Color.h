/*
 * Color.h
 *
 *  Created on: 29-Oct-2011
 *      Author: apurv
 */

#ifndef COLOR_H_
#define COLOR_H_

class Color {
	int red;
	int green;
	int blue;
public:
	Color(int r, int g, int b);
	virtual ~Color();
    int getBlue();
    int getGreen();
    int getRed();
    void setBlue(int blue);
    void setGreen(int green);
    void setRed(int red);
    void printColor();

    void addMoreRed(int deltaRed);
    void addMoreGreen(int deltaGreen);
    void addMoreBlue(int deltaBlue);
};

#endif /* COLOR_H_ */
