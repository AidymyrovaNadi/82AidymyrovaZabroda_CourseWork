#include <algorithm>
#include <math.h>
#include <functional>
#include "Segments.h"
#include "GeomLines.h"
#include "RecordSolution.h"
#include "Rand.h"
#include "main.h"

using namespace std;

int RecordSolution::Find(double** linesArr, int* solutions, int rows, Segments segments)
{
    for (int i = 0; i < rows - 1; ++i)
    {
        for (int j = 0; j < rows - i - 1; ++j)
        {
            if (solutions[j] < solutions[j + 1])
            {
                int b = solutions[j];
                solutions[j] = solutions[j + 1];
                solutions[j + 1] = b;

                RecordProg.swapRows(linesArr[j], linesArr[j + 1]);
            }
        }
    }


    optimumLine.k = linesArr[0][0];
    optimumLine.A = linesArr[0][1];

    optimumVal = optimumLine.Intersection(optimumLine.k, optimumLine.A, segments);

    return optimumVal;
}

void RecordSolution::Print()
{
    printf("\n\n Поточний рекордний розв'язок: [%0.2f; %0.2f].\n", optimumLine.k, optimumLine.A);
    printf(" Рiвняння прямої: ");
    optimumLine.EquationOutput(optimumLine.k, optimumLine.A);
    printf("\n ЦФ рекордного розв'язку: %d.", optimumVal);
}