#include "howitzer.h"
#include "projectile.h"

Howitzer::Howitzer()
{
	// initialize variables
	angle = 0;
	degrees = 0;
	age = -1;
	ready = true;
}

double Howitzer::getAngle()
{
	return angle;
}

Position Howitzer::getPosition() const
{
	return position;
}

void Howitzer::adjustAngle(const Interface *ui)
{
	// move by a lot
	if (ui->isRight())
		 angle += 0.05;
	if (ui->isLeft())
		angle -= 0.05;

   // move by a little
	if (ui->isUp())
		angle += (angle >= 0 ? -0.003 : 0.003);
	if (ui->isDown())
		angle += (angle >= 0 ? 0.003 : -0.003);
	degrees = angle * 180 / 3.14;
	
	return;
}

void Howitzer::fire(const Interface *ui)
{
	// set age to 0 so main can initialize a projectile, but only if there aren't other projectiles
	if (age == -1)
		if (ui->isSpace())
			age = 0;

	return;
}

void Howitzer::drawHowitzer(ogstream& gout)
{
	gout.drawHowitzer(position, angle, age);
	return;
}