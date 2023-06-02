#include "physics.h"
#include <vector>

double Physics::interpolate(vector<double> xData, vector<double> yData, double x) {

    int vecSize = xData.size();
    int i = 0;

    if (x >= xData[vecSize - 2])
    {
        i = vecSize - 2;  // use second to last value because we need one larger for interpolation
    }

    else
    {
        while (x > xData[i + 1]) i++;
    }
    double xL = xData[i];
    double yL = yData[i];
    double xR = xData[i + 1];
    double yR = yData[i + 1];

    double dxdy = (yR - yL) / (xR - xL);

    double ddy = yL + dxdy * (x - xL);
    return ddy;
}