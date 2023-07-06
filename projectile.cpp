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
    
    //cout << y << "\n";
    //cout << ddy << "\n";
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
    /* cout << dy << "\n";*/
}

bool isFlying()
{
    return true;
}

void Projectile::drawProjectile(ogstream& gout)
{
	gout.drawProjectile(position, age);
}

//int main()
//{
//    TestHowitzer hTest;
//    Howitzer howitzer;
//    TestPhysics test;
//    Physics physics;
//    /*
//    * Only for testing
//    */
//    test.main();
//    hTest.main();
//
//    double angleDeg;
//    double angleRad;
//    // horizontal and vertical components of velocity
//    double dx;
//    double dy;
//    // time in seconds
//    double time = .01;
//    double hangtime = 0;
//    // horizontal and vertical distance
//    double x = 0;
//    double y = 0;
//    // horizontal and vertical components of acceleration
//    double ddx = 0;
//    // gravity 
//    double ddy = 0;
//    // drag
//    double drag = 0;
//    // velocity
//    double velocity = 0;
//    // current angle
//    double angle_from_components = 0;
//    // air density
//    double air_density = 0;
//    // current speed of sound
//    double mach_curr = 0;
//    // current drag coefficient
//    double coefficient = 0;
//    double last_y = 0;
//    double last_x = 0;
//    double last_time = 0;
//    
//
//    cout << "What is the angle of the howitzer where 0 is up? ";
//    cin >> angleDeg;
//    angleRad = (angleDeg / 360) * 2 * (atan(1) * 4);
//
//    dx = sin(angleRad) * physics.INIT_SPEED;
//    dy = cos(angleRad) * physics.INIT_SPEED;
//
//
//    
//
//    vector<double> yGrav = { 0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 15000, 20000, 25000 };
//    vector<double> fGrav= { -9.807, -9.804, -9.801, -9.797, -9.794, -9.791, -9.788, -9.785, -9.782, -9.779, -9.776, -9.761, -9.745, -9.730 };
//
//    vector<double> altitude = { 0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 15000, 20000, 25000, 30000, 40000, 50000, 60000, 70000, 80000 };
//    vector<double> density = { 1.2250000, 1.1120000, 1.0070000, 0.9093000, 0.8194000, 0.7364000, 0.6601000, 0.5900000, 0.5258000, 0.4671000, 0.4135000, 0.1948000, 0.0889100, 0.0400800, 0.0184100, 0.0039960, 0.0010270, 0.0003097, 0.0000828, 0.0000185 };
//    
//    vector<double> mach = { 0.300, 0.500, 0.700, 0.890, 0.920, 0.960, 0.980, 1.000, 1.020, 1.060, 1.240, 1.530, 1.990, 2.870, 2.890, 5.000 };
//    vector<double> drag_coefficient = { 0.1629, 0.1659, 0.2031, 0.2597, 0.3010, 0.3287, 0.4002, 0.4258, 0.4335, 0.4483, 0.4064, 0.3663, 0.2897, 0.2297, 0.2306, 0.2656 };
//    
//    vector<double> speed_of_sound = { 340, 336, 332, 328, 324, 320, 316, 312, 308, 303, 299, 295, 295, 295, 305, 324 }; \
//
//    while (y >= 0)
//    {
//
//        //drag calculation
//        velocity = sqrt((dx * dx) + (dy * dy));
//        angle_from_components = atan2(dx, dy);
//        air_density = physics.interpolate(altitude, density, y);
//        mach_curr = physics.interpolate(altitude, speed_of_sound, y);
//        coefficient = physics.interpolate(mach, drag_coefficient, velocity / mach_curr);
//        drag = (0.5 * coefficient * air_density * (velocity * velocity) * physics.AREA) / physics.WEIGHT;
//
//        ddx = -sin(angle_from_components) * drag;
//        ddy = physics.interpolate(yGrav, fGrav, y) - cos(angle_from_components) * drag;
//
//        //cout << y << "\n";
//        //cout << ddy << "\n";
//        // adjust velocity for acceleration
//        dx += ddx * time;
//        dy += ddy * time;
//        // adjust postion for acceleration and velocity
//        last_y = y;
//        last_x = x;
//        last_time = hangtime;
//        y = y + dy * time + (.5 * ddy * time * time);
//        x = x + dx * time + (.5 * ddx * time * time);
//        /* cout << dy << "\n";*/
//        hangtime += time;
//    };
//
//
//    vector<double> last_y_value = { y, last_y };
//    vector<double> x_value = { x, last_x };
//    vector<double> time_value = { hangtime, last_time };
//    x = physics.interpolate(last_y_value, x_value, 0);
//    hangtime = physics.interpolate(last_y_value, time_value, 0);
//
//    cout << fixed;
//    cout << setprecision(1);
//    cout << "Distance " << x << "\n";
//    cout << "Hang Time: " << hangtime << "\n";
//
//    double grav3 = physics.interpolate(mach, drag_coefficient, 5);
//    cout << grav3;
//}
