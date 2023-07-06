/*************************************************************
 * 1. Name:
 *      Spencer Sorenson, Jacob Gunderson
 * 2. Assignment Name:
 *      Lab 08: M777 Howitzer
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 * 4. What was the hardest part? Be as specific as possible.
 *      Interpolation and drag
 * 5. How long did it take for you to complete the assignment?
 *      5 hours
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "ground.h"     // for GROUND
#include "position.h"   // for POSITION
#include "physics.h"    // for PHYSICS
#include "testPhysics.h" // ONLY FOR TESTING 
#include "testHowitzer.h"
#include "howitzer.h"
#include "projectile.h"
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
   Demo(Position ptUpperRight) :
      ptUpperRight(ptUpperRight),
      ground(ptUpperRight),
      time(0.0),
      angle(0.0)
   {
      // Set the horizontal position of the howitzer. This should be random.
      //ptHowitzer.setPixelsX(Position(ptUpperRight).getPixelsX() / 2.0);
      howitzer.position.setPixelsX(Position(ptUpperRight).getPixelsX() / 2.0);

      // Generate the ground and set the vertical position of the howitzer.
      //ground.reset(ptHowitzer);
      ground.reset(howitzer.position);

      // This is to make the bullet travel across the screen. Notice how there are 
      // 20 pixels, each with a different age. This gives the appearance
      // of a trail that fades off in the distance.
      for (int i = 0; i < 20; i++)
      {
         projectilePath[i].setPixelsX((double)i * 2.0);
         projectilePath[i].setPixelsY(ptUpperRight.getPixelsY() / 1.5);
      }
   }

   Ground ground;                 // the ground
   Physics physics;               // phyics
   Position  projectilePath[20];  // path of the projectile
   Position  ptHowitzer;          // location of the howitzer
   Position  ptUpperRight;        // size of the screen
   Howitzer howitzer;
   Projectile* projectile = NULL;
   double angle;                  // angle of the howitzer 
   double time;                   // amount of time since the last firing
   int counter;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Demo* pDemo = (Demo*)p;

   //
   // accept input
   //
   pDemo->howitzer.adjustAngle(pUI);

   // fire that gun
   pDemo->howitzer.fire(pUI);

   //
   // perform all the game logic
   //

   // advance time by half a second.
   if (pDemo->howitzer.age == 0)
   {
       pDemo->projectile = new Projectile(pDemo->howitzer.position, pDemo->howitzer.getAngle());
       pDemo->howitzer.age += 0.5;
   }
   else if (pDemo->howitzer.age > 0)
   {
    /*   while (pDemo->counter < 20)
       {
           pDemo->projectile = new Projectile(pDemo->howitzer.position, pDemo->howitzer.getAngle());
           Position pos = pDemo
           pDemo->projectilePath[pDemo->counter].setPixelsX;
       }*/
       // move the projectile across the screen
       pDemo->projectile->update();
       Position pos = pDemo->projectile->getPosition();

       // tail of 20 pixels
       for (int i = 0; i < 20; i++)
       {
           pDemo->projectilePath[i].setPixelsX(pos.getPixelsX() - 10);
           pDemo->projectilePath[i].setPixelsY(pos.getPixelsY() - 10);
       }
       Position target = pDemo->ground.getTarget();
       if (computeDistance(pos, target) <= 200)
       {
           pDemo->ground.reset(pDemo->howitzer.position);
       }
       if (pDemo->ground.getElevationMeters(pos) <= pos.getMetersY())
            pDemo->howitzer.age += 0.5;
       else
           pDemo->howitzer.age = -1;
   }

   // Hit target

   
  


   //
   // draw everything
   //

   ogstream gout(Position(10.0, pDemo->ptUpperRight.getPixelsY() - 20.0));

   // draw the ground first
   pDemo->ground.draw(gout);

   // draw the howitzer
   gout.drawHowitzer(pDemo->howitzer.getPosition(), pDemo->howitzer.getAngle(), pDemo->howitzer.age);

   // draw the projectile
   //for (int i = 0; i < 20; i++)
   //   gout.drawProjectile(pDemo->projectilePath[i], 0.5 * (double)i);
   if (pDemo->howitzer.age >= 0)
   {
       pDemo->projectile->drawProjectile(gout);
       gout << "Altitude: " 
           << pDemo->projectile->getPosition().getMetersY() << "m \n";
       gout << "Speed: "
           << pDemo->projectile->getVelocity() << "m/s \n";
       gout << "Distance: "
           << pDemo->projectile->getPosition().getMetersX() - pDemo->howitzer.getPosition().getMetersX() << "m \n";
       gout << "Hangtime: "
           << pDemo->howitzer.age << "s\n";
   }

   // draw some text on the screen
   gout.setf(ios::fixed | ios::showpoint);
   gout.precision(1);
   gout << "Angle: "
       << pDemo->howitzer.degrees << "degrees \n";
 

   pDemo->counter += 1;
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setPixelsX(700.0);
   ptUpperRight.setPixelsY(500.0);
   Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
   Interface ui(0, NULL,
      "Demo",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Demo demo(ptUpperRight);

   // set everything into action
   ui.run(callBack, &demo);


   return 0;
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
