/***********************************************************************
 * Header File:
 *    Howitzer : The representation of a howitzer
 * Author:
 *    Jacob Gunderson and Spencer Sorenson
 * Summary:
 *    Everything we need to know about the howitzer
 ************************************************************************/
#pragma once

#include "position.h"
#include "ground.h"
#include "uiInteract.h"
#include "uiDraw.h"
using namespace std;


class Howitzer
{

public:

	double getAngle();
	Position getPosition();
	void adjustAngle(Interface& ui);
	void fire(Interface & ui);
	void drawHowitzer(ogstream & gout);

private:
	double angle;
	Position position;
	double age;
	Ground ground;

};