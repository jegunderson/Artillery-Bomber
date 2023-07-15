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


/***********************************************************
 * Howitzer
 * The howitzer class
 ***********************************************************/

class Howitzer
{

public:
	Howitzer();
	double getAngle();
	Position getPosition() const;
	void adjustAngle(const Interface *ui);
	void fire(const Interface *ui);
	void drawHowitzer(ogstream & gout);
	double angle;
	double degrees;
	Position position;
	Ground ground;
	bool ready;
	double age;

private:
	Interface ui;
};