#pragma once

using namespace std;

class Main
{
public:
    static void swapRows(double* R1, double* R2)
    {
        double temp;
        for (int j = 0; j < 2; j++)
        {
            temp = R1[j];
            R1[j] = R2[j];
            R2[j] = temp;
        }
    }

    Rand random;
};

