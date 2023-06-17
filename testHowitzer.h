/***********************************************************************
 * Header File:
 *    Test Howitzer : Test the howitzer class
 * Author:
 *    Jacob Gunderson and Spencer Sorenson
 * Summary:
 *    All the unit tests for the Howitzer class
 ************************************************************************/
#pragma once

#include "howitzer.h"
#include <cassert>
#include <vector>

using namespace std;

/*******************************
 * TEST HOWITZER
 * A friend class for Howitzer which contains the howitzer unit tests
 ********************************/
class TestHowitzer
{
public:
    void run()
    {
        getAngleNormal();
        getAngleHigh();
        getAngleNegative();
        getPositionNormal();
        getPositionHigh();
        getPositionInvalid();
        adjustAngleNormal();
        fireNormal();

    }

private:
    Interface ui;

    void getAngleNormal()
    {
        //Setup
        Howitzer h;
        h.angle = 10;
        //Exercise
        double angle = h.getAngle();
        //Verify
        assert(angle == 10);
    }

    void getAngleHigh()
    {
        //Setup
        Howitzer h;
        h.angle = 400;
        //Exercise
        double angle = h.getAngle();
        //Verify
        assert(angle == 400);
    }

    void getAngleNegative()
    {
        //Setup
        Howitzer h;
        h.angle = -45;
        //Exercise
        double angle = h.getAngle();
        //Verify
        assert(angle == -45);
    }

    void getPositionNormal()
    {
        //Setup
        Howitzer h;
        h.position = Position(45, 45);
        //Exercise
        Position position = h.getPosition();
        double x = position.getPixelsX();
        double y = position.getPixelsY();
        //Verify
        assert(x == 45);
        assert(y == 45);
    }

    void getPositionHigh()
    {
        //Setup
        Howitzer h;
        h.position = Position(450, 450);
        //Exercise
        Position position = h.getPosition();
        double x = position.getPixelsX();
        double y = position.getPixelsY();
        //Verify
        assert(x == 450);
        assert(y == 450);
    }
    
    void getPositionInvalid()
    {
        //Setup
        Howitzer h;
        h.position = Position(-450, -450);
        //Exercise
        Position position = h.getPosition();
        double x = position.getPixelsX();
        double y = position.getPixelsY();
        //Verify
        assert(x == -450);
        assert(y == -450);
    }    
    
    void adjustAngleNormal()
    {
        // Setup
        Howitzer h;
        // Exercise
        h.adjustAngle(ui);
        double angle = h.getAngle();
        // Verify
        assert(angle != 0);
        // Teardown
    }

    void fireNormal()
    {
        // Setup
        Howitzer h;
        // Exercise
        h.fire(ui);
        // Verify
        assert(1 != 0);
        // Teardown
    }



}