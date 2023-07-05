/***********************************************************************
 * Header File:
 *    Projectile : The representation of a projectile
 * Author:
 *    Jacob Gunderson and Spencer Sorenson
 * Summary:
 *    Everything we need to know about the projectile
 ************************************************************************/
#pragma once

#include "position.h"
#include "physics.h"
#include "howitzer.h"
#include "ground.h"
#include "uiDraw.h"
using namespace std;


class Projectile
{

public:
	Projectile(Position& ptHowitzer, double angle);
	Position getPosition();
	void calcVelocity();
	void calcAngle();
	void calcAirDensity();
	void calcDrag();
	void setPosition(Position &newPosition);
	void drawProjectile(ogstream& gout);
	Ground ground;

private:
	Position position;
	double age;
	double dx;
	double dy;
	double velocity;
	Physics physics;
	double air_density;
	double gravity;
	double drag;
};