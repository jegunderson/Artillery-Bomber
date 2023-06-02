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

	double interpolate(vector<double> xData, vector<double> yData, double x);



};