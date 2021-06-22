#include <cstdlib>
#include <time.h>
#include "Rand.h"

double Rand::Double(double min, double max)
{
    return (double)(rand()) / RAND_MAX * (max - min) + min;
}

int Rand::Int(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}