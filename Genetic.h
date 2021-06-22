#pragma once
#include <string>
#include "Segments.h"
#include "GeomLines.h"
#include "RecordSolution.h"
#include "Rand.h"

using namespace std;

class Parents;
class Children;
class Mutation;
class NewPopulation;

class Parents
{
public:
	int parentsNum = 2;
	GeomLines parents;
	int maxVal = 0, i_max = 0, i_rand = 0;

	double** ChooseParents(int populationRows, double** populationLinesArr, int* populationSolutions, Segments segments, double** parentsLines);
};

class Children
{
public:
	GeomLines children;
	GeomLine Child;
	int childNum;
	double minK = 0, maxK = 0, minA = 0, maxA = 0;
	double q = 0;
	double* Q = new double[childNum];

	double* CreateChild(double** parentsArr, Segments segments, double* arr);
	double** ChildrenArr(double** parentsArr, Segments segments, double** childrenArr);
	double* DiscreteIntervals(double** parentsArray, bool ifMutation, Segments segments, double* arr);
};

class Mutation : public Children
{
public:
	double p = 0;
	bool ifMutation = 0;
	GeomLine mutation;
	GeomLines MutationArr;
	
	double* MutationChild(double** parentsArr, double* child, double q, Segments segments, double* mutat);
};

class NewPopulation
{
public:
	GeomLines newPopulation;

	double** UpdPopulation(double** populationLinesArr, int* populationSolutions, int populationRows, double** childLinesArr, int* childSolutions, int childrenRows, Segments segments, double** NewPopulArr);
};

class Genetic
{
public:
	GeomLines GeneticSolution;
	int iteration;
	int rows;
	RecordSolution optimum;

	Parents parentsClass;
	Children childrenClass;
	Mutation mutationClass;
	NewPopulation newPopulationClass;

	double** algorithm(double** geneticLinesArr, int rows, Segments segments, bool print);
};