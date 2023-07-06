/***********************************************************************
 * Header File:
 *    Physics : The representation of a physics 
 * Author:
 *    Jacob Gunderson and Spencer Sorenson
 * Summary:
 *    Everything we need to know about a acceleration, velocity, gravity, drag, and air density's affect on an object
 ************************************************************************/
#pragma once

#include <cmath>
#include <vector>
#include <iostream>
using namespace std;


class Physics
{

public:
	double INIT_SPEED = 827;
	double WEIGHT = 46.7;
	double DIAMETER = .15489;
	double AREA = (atan(1) * 4) * (DIAMETER / 2) * (DIAMETER / 2);

	double angleDeg;
	double angleRad;
	double dx;
	double dy;
	double x = 0;
	double y = 0;

	double interDrag(double x) 
	{
		vector<double> mach = { 0.300, 0.500, 0.700, 0.890, 0.920, 0.960, 0.980, 1.000, 1.020, 1.060, 1.240, 1.530, 1.990, 2.870, 2.890, 5.000 };
		vector<double> dragCo = { 0.1629, 0.1659, 0.2031, 0.2597, 0.3010, 0.3287, 0.4002, 0.4258, 0.4335, 0.4483, 0.4064, 0.3663, 0.2897, 0.2297, 0.2306, 0.2656 };
		return interpolate(mach, dragCo, x);
	};

	double interAirD(double y) 
	{
		vector<double> altitude = { 0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 15000, 20000, 25000, 30000, 40000, 50000, 60000, 70000, 80000 };
		vector<double> density = { 1.2250000, 1.1120000, 1.0070000, 0.9093000, 0.8194000, 0.7364000, 0.6601000, 0.5900000, 0.5258000, 0.4671000, 0.4135000, 0.1948000, 0.0889100, 0.0400800, 0.0184100, 0.0039960, 0.0010270, 0.0003097, 0.0000828, 0.0000185 };
		return interpolate(altitude, density, y);
	};
	double interSpeedS(double x) 
	{
		vector<double> altitude = { 0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 15000, 20000, 25000, 30000, 40000 };
		vector<double> speedSound = { 340, 336, 332, 328, 324, 320, 316, 312, 308, 303, 299, 295, 295, 295, 305, 324 };
		return interpolate(altitude, speedSound, x);
	};
	double interGrav(double x) 
	{
		vector<double> altitude = { 0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 15000, 20000, 25000 };
		vector<double> fGrav = { -9.807, -9.804, -9.801, -9.797, -9.794, -9.791, -9.788, -9.785, -9.782, -9.779, -9.776, -9.761, -9.745, -9.730 };
		return interpolate(altitude, fGrav, x);
	};

	double interpolate(vector<double> xData, vector<double> yData, double x);



};