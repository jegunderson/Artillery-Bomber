#include "projectile.h"

Projectile::Projectile(Position& ptHowitzer, double angle)
{
	position = ptHowitzer;
	age = 0.0;
    radians = angle;
    dx = sin(radians) * physics.INIT_SPEED;
    dy = cos(radians) * physics.INIT_SPEED;
	velocity = 0.0;
	air_density = 0.0;
	gravity = 0.0;
	drag = 0.0;
    x = position.getMetersX();
    y = position.getMetersY();
    time = .5;
    hangtime = 0.0;
}

Position Projectile::getPosition()
{
	return position;
}

double Projectile::getVelocity()
{
    
	return velocity;
}

void Projectile::calcAngle()
{
	return;
}

void Projectile::calcAirDensity()
{
    air_density = physics.interAirD(y);
    return;
}

void Projectile::calcDrag()
{
    //drag calculation

    velocity = sqrt((dx * dx) + (dy * dy));
    calcAirDensity();
    double mach_curr = physics.interSpeedS(y);
    double coefficient = physics.interDrag(velocity / mach_curr);
    drag = (0.5 * coefficient * air_density * (velocity * velocity) * physics.AREA) / physics.WEIGHT;
	return;
}

void Projectile::setPosition(Position& newPosition)
{
	position = newPosition;
}

void Projectile::update()
{
    calcDrag();
    double angle_from_components = atan2(dx, dy);
    ddx = -sin(angle_from_components) * drag;
    ddy = physics.interGrav(y) - cos(angle_from_components) * drag;
    
    // adjust velocity for acceleration
    dx += ddx * time;
    dy += ddy * time;
    // adjust postion for acceleration and velocity
    double last_y = y;
    double last_x = x;
    double last_time = hangtime;
    y = y + dy * time + (.5 * ddy * time * time);
    x = x + dx * time + (.5 * ddx * time * time);
    Position newPosition(x, y);
    setPosition(newPosition);
}

bool isFlying()
{
    return true;
}

void Projectile::drawProjectile(ogstream& gout)
{
	gout.drawProjectile(position, age);
}
