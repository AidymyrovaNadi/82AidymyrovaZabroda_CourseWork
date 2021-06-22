#include <algorithm>
#include <string>
#include "GeomLines.h"
#include "RecordSolution.h"
#include "Greedy.h"

using namespace std;

double** Greedy::InitSolutions(int& rows)
{
    if (rows == 0) rows = 20;
    GreedySolutions.linesArr = new double* [rows];
    for (int i = 0; i < rows; i++) GreedySolutions.linesArr[i] = new double[2];

    for (int i = 0; i < rows / 2; i++) {
        GreedySolutions.linesArr[i][0] = i;
        GreedySolutions.linesArr[i][1] = 0;
    }
    for (int i = rows / 2; i < rows; i++) {
        GreedySolutions.linesArr[i][0] = 0;
        GreedySolutions.linesArr[i][1] = i - (rows / 2);
    }

    return GreedySolutions.linesArr;
}

void Greedy::algorithm(int rows, Segments segments)
{
    double** greedyArr = GreedySolutions.linesArr;
    greedyArr = InitSolutions(rows);

    int* solutionsArr = GreedySolutions.solutions;
    solutionsArr = GreedySolutions.IntersectionArr(greedyArr, rows, segments);

    GreedySolutions.PrintTable(greedyArr, rows, solutionsArr);
    

    optimum.Find(greedyArr, solutionsArr, rows, segments);
    optimum.Print();

}