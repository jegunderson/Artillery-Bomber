/*************************************************************
 * 1. Name:
 *      Spencer Sorenson, Jacob Gunderson
 * 2. Assignment Name:
 *      Lab 13: M777 Howitzer
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
      ground(ptUpperRight)
   {
      // Set the horizontal position of the howitzer. This should be random.
      howitzer.position.setPixelsX(Position(ptUpperRight).getPixelsX() / 2.0);

      // Generate the ground and set the vertical position of the howitzer.
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
   Howitzer howitzer;             // the howitzer
   Projectile* projectile = NULL; // the projectile
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
       // move the projectile across the screen
       pDemo->projectile->update();
       Position pos = pDemo->projectile->getPosition();

       // tail of 20 pixels
       for (int i = 0; i < 20; i++)
       {
           pDemo->projectilePath[i].setPixelsX(pos.getPixelsX() - 10);
           pDemo->projectilePath[i].setPixelsY(pos.getPixelsY() - 10);
       }
       
       // Hit target       
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



   
  


   //
   // draw everything
   //

   ogstream gout(Position(10.0, pDemo->ptUpperRight.getPixelsY() - 20.0));

   // draw the ground first
   pDemo->ground.draw(gout);

   // draw the howitzer
   gout.drawHowitzer(pDemo->howitzer.getPosition(), pDemo->howitzer.getAngle(), pDemo->howitzer.age);

   // draw the projectile and metrics if projectile has been fired
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