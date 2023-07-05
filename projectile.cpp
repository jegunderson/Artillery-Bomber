#include "projectile.h"

Projectile::Projectile(Position& ptHowitzer, double angle)
{
	position = ptHowitzer;
	age = 0.0;
	dx = 0.0;
	dy = 0.0;
	velocity = 0.0;
	air_density = 0.0;
	gravity = 0.0;
	drag = 0.0;
}

Position Projectile::getPosition()
{
	return position;
}

void Projectile::calcVelocity()
{
	return;
}

void Projectile::calcAngle()
{
	return;
}

void Projectile::calcAirDensity()
{
	return;
}

void Projectile::calcDrag()
{
	return;
}

void Projectile::setPosition(Position& newPosition)
{
	position = newPosition;
}

void Projectile::drawProjectile(ogstream& gout)
{
	gout.drawProjectile(position, age);
}
