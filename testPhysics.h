/***********************************************************************
 * Header File:
 *    Test Physics : Test the physics class
 * Author:
 *    Jacob Gunderson
 * Summary:
 *    All the unit tests for the Physics class
 ************************************************************************/
#pragma once

#include "physics.h"
#include <cassert>
#include <vector>

using namespace std;

/*******************************
 * TEST GROUND
 * A friend class for Ground which contains the Ground unit tests
 ********************************/
class TestPhysics
{
public:

    void main()
    {
        run();
        cout << "All physics tests pass" << endl;
    }
    void run()
    {
        // Test Interpolate Drag
        interDragHigh();
        interDragNormal();
        // Test Interpolate Air Density
        interAirDNormal();
        interAirDZero();
        // Test Interpolate Speed of Sound
        interSpeedSZero();
        interSpeedSNormal();
        // Test Interpolate Gravity
        interGravZero();
        interGravNormal();
        // Test Interpolate
        interpolateBottom();
        interpolateAbove();

    }

private:
    void interDragHigh()
    {
        // Setup
        Physics p;
        double x = 5;
        // Exercise
        double y = p.interDrag(x);
        // Verify
        assert(y > 0);
        assert(y == 0.2656);
        // Teardown
    }

    void interDragNormal()
    {
        // Setup
        Physics p;
        double x = .6;
        // Exercise
        double y = p.interDrag(x);
        // Verify
        assert(y > 0.1659);
        assert(y < 0.2031);
        // Teardown
    }

    void interAirDNormal()
    {
        // Setup
        Physics p;
        double x = 6363;
        //Exercise
        double y = p.interAirD(x);
        // Verify
        assert(y > 0);
        assert(y < 0.6601000 );
        assert(y > 0.5900000);
        // Teardown
    }

    void interAirDZero()
    {
        // Setup
        Physics p;
        double x = 0;
        // Exercise
        double y = p.interAirD(x);
        // Verify
        assert(y > 0);
        assert(y == 1.2250000);
        // Teardown
    }

    void interSpeedSZero()
    {
        // Setup
        Physics p;
        double x = 0;
        // Exercise
        double y = p.interSpeedS(x);
        // Verify
        assert(y > 0);
        assert(y == 340);
        // Teardown
    };

    void interSpeedSNormal()
    {
        // Setup
        Physics p;
        double x = 3500;
        // Exercise
        double y = p.interSpeedS(x);
        // Verify
        assert(y < 328);
        assert(y > 324);
        // Teardown
    }

    void interGravZero()
    {
        // Setup
        Physics p;
        double x = 0;
        // Exercise
        double y = p.interGrav(x);
        // Verify
        assert(y < 0);
        assert(y == -9.807);
        // Teardown
    };

    void interGravNormal()
    {
        // Setup
        Physics p;
        double x = 1235;
        // Exercise
        double y = p.interGrav(x);
        // Verify
        assert(y > -9.804);
        assert(y < -9.801);
        // Teardown
    };

    void interpolateBottom()
    {
        // Setup
        Physics p;
        vector<double> xData = { 100, 500, 700, 1000, 1200 };
        vector<double> yData = { 3, 7, 8, 10, 10.5 };
        double x = xData[0];
        // Exercise
        double y = p.interpolate(xData, yData, x);
        // Verify
        assert(y = yData[0]);
        // Teardown
    }

    void interpolateAbove()
    {
        // Setup
        Physics p;
        vector<double> xData = { 100, 500, 700, 1000, 1200 };
        vector<double> yData = { 3, 7, 8, 10, 10.5 };
        double x = 2000;
        // Exercise
        double y = p.interpolate(xData, yData, x);
        // Verify
        assert(y = 10.5);
        // Teardown
    }

};
