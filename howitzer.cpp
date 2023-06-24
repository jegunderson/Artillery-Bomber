#include "howitzer.h"


double Howitzer::getAngle()
{
	return angle;
}

Position Howitzer::getPosition()
{
	return position;
}

void Howitzer::adjustAngle(const Interface *ui)
{
	if (ui->isLeft())
		if (angle <= -1.5708)
			angle -= .05;
	else if (ui->isRight())
		if (angle >= 1.5708)
			angle += .05;
	else if (ui->isUp())
		if (angle < 0)
			angle += .003;
	else if (angle > 0)
		angle -= .003;
	else if (ui->isDown())
		if (angle < 0)
			angle -= .003;
	else if (angle > 0)
		angle += .003;
	
	return;
}

void Howitzer::fire(const Interface *ui)
{
	if (ui->isSpace())
		age = 0;
		//create instance of projectile once class is created.
	return;
}

void Howitzer::drawHowitzer(ogstream& gout)
{
	gout.drawHowitzer(position, angle, age);
	return;
}