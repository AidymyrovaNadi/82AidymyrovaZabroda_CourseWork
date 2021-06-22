#include <algorithm>
#include <math.h>
#include "GeomLines.h"
#include "Segments.h"
#include "Rand.h"
#include "main.h"

using namespace std;

GeomLine geomLine;

double* GeomLine::LineInit() {
    line = new double[columns];
    return line;
}

double** GeomLines::ArrInit(int& rows)
{
    if (rows == 0) rows = 10;
    linesArr = new double* [rows];
    for (int i = 0; i < rows; i++) linesArr[i] = new double[columns];

    for (int i = 0; i < rows; i++) {
        linesArr[i] = geomLine.LineInit();
    }

    return linesArr;
}

double* GeomLine::LineFill()
{
    line = new double[columns]; // [k; A]

    for (int i = 0; i < columns; i++) {
        line[i] = (random.Double(-7, 7));
    }

    return line;
}

double** GeomLines::ArrFill(int& rows)
{
    if (rows == 0) rows = 10;
    linesArr = new double* [rows];
    for (int i = 0; i < rows; i++) linesArr[i] = new double[columns];

    for (int i = 0; i < rows; i++) {
        linesArr[i] = geomLine.LineFill();
    }

    return linesArr;
}

int GeomLine::Intersection(double k, double A, Segments segments)
{
    double k1 = 0, a1 = 0, x, y;
    double x1, x2, y1, y2;
    int counter = 0;

    for (int i = 0; i < segments.rows; i++)
    {
        x1 = segments.arr[i][0];
        x2 = segments.arr[i][2];
        y1 = segments.arr[i][1];
        y2 = segments.arr[i][3];

        a1 = (y2 - y1) / (x2 - x1);
        k1 = (x2 * y1 - x1 * y2) / (x2 - x1);

        if (a1 == A) continue; //printf(" Пряма та вiдрiзок паралельнi.\n");
        else
        {
            x = (k1 - k) / (A - a1);
            y = a1 * x + k1;

            if (((x >= x1 && x <= x2) || (x >= x2 && x <= x1)) && (y >= y1 && y <= y2) || (y >= y2 && y <= y1))
            {
                counter++;
            }
        }
    }

    return counter;
}

int* GeomLines::IntersectionArr(double** linesArr, int rows, Segments segments)
{
    solutions = new int[rows];

    for (int i = 0; i < rows; i++)
    {
        solutions[i] = geomLine.Intersection(linesArr[i][0], linesArr[i][1], segments);
    }

    return solutions;
}

void GeomLine::EquationOutput(double k, double A)
{
    if (A < 0) printf("y = %0.2f - %0.2fx", k, fabsf(A));
    else printf("y = %0.2f + %0.2fx", k, A);
}

void GeomLine::PrintSolution()
{
    printf(" Пряма [%0.2f; %0.2f] перетинає вiдрiзкiв: %d. ", k, A, solutionVal);
}

void GeomLines::PrintSolutions(double** linesArr, int rows, int* solutions)
{
    for (int i = 0; i < rows; i++)
    {
        printf("\n Пряма №%d - [%0.2f; %0.2f] - перетинає вiдрiзкiв: %d. ", i + 1, linesArr[i][0], linesArr[i][1], solutions[i]);
    }    
}

void GeomLines::PrintTable(double** linesArr, int rows, int* solutions)
{
    printf("\n ");
    for (int i = 0; i < 88; i++) printf("-");

    printf("\n |  №\t|\tk\t|\tA\t|\t     Рiвняння    \t|\tЦФ\t|\n ");
    for (int i = 0; i < 88; i++) printf("-");

    for (int i = 0; i < rows; i++)
    {
        if (linesArr[i][1] < 0) printf("\n |  %d\t|     %0.2f \t|     %0.2f \t|\t y = %0.2f - %0.2fx \t|\t%d\t|", i + 1, linesArr[i][0], linesArr[i][1], linesArr[i][0], fabs(linesArr[i][1]), solutions[i]);
        else printf("\n |  %d\t|     %0.2f \t|     %0.2f \t|\t y = %0.2f + %0.2fx \t|\t%d\t|", i + 1, linesArr[i][0], linesArr[i][1], linesArr[i][0], linesArr[i][1], solutions[i]);
    }

    printf("\n ");
    for (int i = 0; i < 88; i++) printf("-");
}