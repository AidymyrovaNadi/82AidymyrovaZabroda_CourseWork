#include <conio.h>
#include <string>
#include "Segments.h"
#include "GeomLines.h"
#include "RecordSolution.h"
#include "Rand.h"
#include "Genetic.h"

using namespace std;

Genetic genetic;

double** Parents::ChooseParents(int populationRows, double** populationLinesArr, int* populationSolutions, Segments segments, double** parentsLines)
{
    parentsLines = parents.ArrInit(parentsNum);

    for (int i = 0; i < populationRows; i++) {
        if (populationSolutions[i] > maxVal || i == 0) {
            maxVal = populationSolutions[i];
            i_max = i;
        }
    }

    i_rand = parents.random.Int(0, populationRows - 1);
    if ((i_rand == i_max) && (i_max != 0)) i_rand--;
    if ((i_rand == i_max) && (i_max != populationRows)) i_rand++;

    for (int i = 0; i < populationRows; i++) {
        if (i == i_max)
        {
            for (int j = 0; j < 2; j++) {
                parentsLines[0][j] = populationLinesArr[i][j];
            }
        }
        if (i == i_rand)
        {
            for (int j = 0; j < 2; j++) {
                parentsLines[1][j] = populationLinesArr[i][j];
            }
        }        
    }

    return parentsLines;
}

double* Children::DiscreteIntervals(double** parentsArray, bool ifMutation, Segments segments, double* arr)
{
    double k1 = 0, k2 = 0, a1 = 0, a2 = 0, alpha;
    double minK, maxK;
    double minA, maxA;

    alpha = children.random.Double(-0.25, 1.25);

    k1 = parentsArray[0][0];
    a1 = parentsArray[0][1];
    k2 = parentsArray[1][0];
    a2 = parentsArray[1][1];

    if (k1 < k2) {
        minK = k1 - (k2 - k1) * alpha;
        maxK = k2 + (k2 - k1) * alpha;
    }
    else {
        minK = k2 - (k1 - k2) * alpha;
        maxK = k1 + (k1 - k2) * alpha;
    }

    if (a1 < a2) {
        minA = a1 - (a2 - a1) * alpha;
        maxA = a2 + (a2 - a1) * alpha;
    }
    else
    {
        minA = a2 - (a1 - a2) * alpha;
        maxA = a1 + (a1 - a2) * alpha;
    }

    int r = 5;

    if (!ifMutation)
    {
        arr[0] = children.random.Double(minK, maxK); // k_new
        arr[1] = children.random.Double(minA, maxA); // A_new
    }
    else
    {
        arr[0] = children.random.Double((children.random.Double((minK - r), minK)), (children.random.Double(maxK, (maxK + r)))); // k_new
        arr[1] = children.random.Double((children.random.Double((minA - r), minA)), (children.random.Double(maxA, (maxA + r)))); // A_new
    }

    return arr;
}

double* Children::CreateChild(double** parentsArr, Segments segments, double* arr)
{
    arr = Child.LineInit();
    arr = DiscreteIntervals(parentsArr, 0, segments, arr);
    return arr;
}

double** Children::ChildrenArr(double** parentsArr, Segments segments, double** childrenArr)
{
    int rows = childNum;

    childrenArr = children.ArrInit(rows);

    for (int i = 0; i < rows; i++) 
    {
        childrenArr[i] = CreateChild(parentsArr, segments, childrenArr[i]);
    }

    return childrenArr;
}

double* Mutation::MutationChild(double** parentsArr, double* child, double q, Segments segments, double* mutat)
{
    p = 0.4;
    mutat = mutation.LineInit();

    if (q >= p)
    {
        mutat = DiscreteIntervals(parentsArr, true, segments, mutat);
    }
    else
    {
        for (int j = 0; j < 2; j++)
        {
            mutat[j] = child[j];
        }
    }

    return mutat;
}

double** NewPopulation::UpdPopulation(double** populationLinesArr, int* populationSolutions, int populationRows, double** childLinesArr, int* childSolutions, int childrenRows, Segments segments, double** NewPopulArr)
{
    int NewPopulRows = populationRows;
    NewPopulArr = newPopulation.ArrInit(NewPopulRows);
        
    // сортируем потомков по возрастанию

    for (int i = 0; i < childrenRows - 1; ++i) {
        for (int j = 0; j < childrenRows - i - 1; ++j) {
            if (childSolutions[j] > childSolutions[j + 1])
            {
                int b = childSolutions[j];
                childSolutions[j] = childSolutions[j + 1];
                childSolutions[j + 1] = b;

                newPopulation.Program.swapRows(childLinesArr[j], childLinesArr[j + 1]);
            }
        }
    }

    // дублируем значения из старой в новую популяцию

    for (int i = 0; i < populationRows; i++) {
        for (int j = 0; j < 2; j++) {
            NewPopulArr[i][j] = populationLinesArr[i][j];
        }
    }

    int* NewPopulSolutions = newPopulation.solutions;
    NewPopulSolutions = newPopulation.IntersectionArr(NewPopulArr, NewPopulRows, segments);
    
    // сортируем популяцию по возрастанию

    for (int i = 0; i < NewPopulRows - 1; ++i) {
        for (int j = 0; j < NewPopulRows - i - 1; ++j) {
            if (NewPopulSolutions[j] > NewPopulSolutions[j + 1])
            {
                int b = NewPopulSolutions[j];
                NewPopulSolutions[j] = NewPopulSolutions[j + 1];
                NewPopulSolutions[j + 1] = b;

                newPopulation.Program.swapRows(NewPopulArr[j], NewPopulArr[j + 1]);
            }
        }
    }

    // замена худших особей на лучших потомков

    int l = 0, k = 0;

    while (l < childrenRows) {
        for (k = 0; k < populationRows; k++) {
            if (NewPopulSolutions[k] == 0 && childSolutions[l] > NewPopulSolutions[k])
            {
                for (int j = 0; j < 2; j++) {
                    NewPopulArr[k][j] = childLinesArr[l][j];
                }
                l++;
                k++;
            }
            else if (NewPopulSolutions[k] != 0 && childSolutions[l] > NewPopulSolutions[k])
            {
                for (int j = 0; j < 2; j++) {
                    NewPopulArr[k][j] = childLinesArr[l][j];
                }
                l++;
                k++;
            }
        }
        l++;
    }

    return NewPopulArr;
}

double** Genetic::algorithm(double** geneticLinesArr, int rows, Segments segments, bool print)
{   
    int* geneticSolutions = GeneticSolution.solutions;

    childrenClass.childNum = rows * 6 / 10;

    geneticSolutions = GeneticSolution.IntersectionArr(geneticLinesArr, rows, segments);

    if (print) {
        printf("\n Початкова популяцiя:");
        GeneticSolution.PrintTable(geneticLinesArr, rows, geneticSolutions);
    }

    double** ChildrenArr = childrenClass.children.linesArr;
    int* ChildrenSolutions = childrenClass.children.solutions;
    int ChildrenRows = childrenClass.childNum;

    ChildrenArr = childrenClass.children.ArrInit(ChildrenRows);

    double* QVals = childrenClass.Q;

    double** MutationArr = mutationClass.MutationArr.linesArr;
    int* MutationSolutions = mutationClass.MutationArr.solutions;
    int MutationRows = childrenClass.childNum;

    MutationArr = mutationClass.MutationArr.ArrInit(MutationRows);

    double** ParentsArr = parentsClass.parents.linesArr;
    int* ParentsSolutions = parentsClass.parents.solutions;
    int parentsRows = parentsClass.parentsNum;

    for (int i = 0; i < ChildrenRows; i++)
    {
        ParentsArr = parentsClass.ChooseParents(rows, geneticLinesArr, geneticSolutions, segments, ParentsArr);
        ParentsSolutions = parentsClass.parents.IntersectionArr(ParentsArr, parentsRows, segments);

        ChildrenArr[i] = childrenClass.CreateChild(ParentsArr, segments, ChildrenArr[i]);
        QVals[i] = childrenClass.children.random.Double(0, 1);

        MutationArr[i] = mutationClass.MutationChild(ParentsArr, ChildrenArr[i], QVals[i], segments, MutationArr[i]);
    }
    
    ChildrenSolutions = childrenClass.children.IntersectionArr(ChildrenArr, ChildrenRows, segments);
    MutationSolutions = mutationClass.MutationArr.IntersectionArr(MutationArr, MutationRows, segments);

    if (print) {
        printf("\n\n Створенi нащадки:");
        childrenClass.children.PrintTable(ChildrenArr, ChildrenRows, ChildrenSolutions);
        printf("\n\n Нащадки пiсля мутацiї:");
        mutationClass.MutationArr.PrintTable(MutationArr, MutationRows, MutationSolutions);
    }

    double** NewPopul = newPopulationClass.newPopulation.linesArr;
    int* NewPopulSolutions = newPopulationClass.newPopulation.solutions;

    NewPopul = newPopulationClass.UpdPopulation(geneticLinesArr, geneticSolutions, rows, MutationArr, MutationSolutions, MutationRows, segments, NewPopul);

    NewPopulSolutions = newPopulationClass.newPopulation.IntersectionArr(NewPopul, rows, segments);

    if (print) {
        printf("\n\n Оновлена популяцiя:");
        newPopulationClass.newPopulation.PrintTable(NewPopul, rows, NewPopulSolutions);
    }

    optimum.Find(NewPopul, NewPopulSolutions, rows, segments);
    if (print) optimum.Print();

    return NewPopul;
}