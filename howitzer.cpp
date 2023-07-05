#include "howitzer.h"


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
	//if (ui->isLeft())
	//	if (angle <= -1.5708)
	//		angle -= .05;
	//else if (ui->isRight())
	//	if (angle >= 1.5708)
	//		angle += .05;
	//else if (ui->isUp())
	//	if (angle < 0)
	//		angle += .003;
	//else if (angle > 0)
	//	angle -= .003;
	//else if (ui->isDown())
	//	if (angle < 0)
	//		angle -= .003;
	//else if (angle > 0)
	//	angle += .003;

	if (ui->isRight())
		 angle += 0.05;
	if (ui->isLeft())
		angle -= 0.05;

   // move by a little
	if (ui->isUp())
		angle += (angle >= 0 ? -0.003 : 0.003);
	if (ui->isDown())
		angle += (angle >= 0 ? 0.003 : -0.003);
	
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