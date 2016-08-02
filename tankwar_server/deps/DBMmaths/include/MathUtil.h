#pragma once

#ifndef __MATHUTIL_H_
#define __MATHUTIL_H_
#include <math.h>

//\===========================================================================================
//\	Light Speed in Meters Per Second
//\===========================================================================================
const int LIGHTSPEED_MS = 299792458;

//\===========================================================================================
//\	Pi
//\===========================================================================================
const float PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062f;

//\===========================================================================================
//\	PHI	 ? / The Golden Ratio
//\===========================================================================================
const float PHI = 1.6180339887f;

//\===========================================================================================
//\	Tau
//\===========================================================================================
const float TAU = 6.283185f;

//\===========================================================================================
//\	EULER
//\===========================================================================================
const float EULER = 2.71828182845904523536028747135266249775724709369995f;

//\===========================================================================================
//\	EULER_MASCHERONI
//\===========================================================================================
const float EULER_MASCHERONI = 0.57721566490153286060651209008240243104215933593992f;

//\===========================================================================================
//\	DEG2RAD		Convert Degrees to Radians
//\===========================================================================================
const float DEG2RAD = 0.01745329252f;

//\===========================================================================================
//\	RAD2DEG		Convert Radians to Degrees
//\===========================================================================================
const float RAD2DEG = 57.295779513f;

//\===========================================================================================
//\	Linearly Interpolate between a and b by m
//\===========================================================================================
float LinearInterpolate(const float a, const float b, const float m);
double LinearInterpolate(const double a, const double b, const double m);
#endif //__MATHUTIL_H_