#pragma once
#include <string>
#include "Segments.h"
#include "GeomLines.h"
#include "RecordSolution.h"

using namespace std;

class Bee
{
public:
	int n_s = 0, m_b = 0, n_f = 0, r = 0;

	GeomLines BeeSolution;
	GeomLine BeeLine;
	GeomLines BestAreas;
	GeomLines Foragers;
	GeomLines BestAreasLocal;
	RecordSolution optimum;

	double** ChooseArea(double** BestAreasArr, double** BeeArr, int* BeeSolutions, int rows);
	double** ForagersInit(double** ForagersArr, double** BestAreasArr);
	double** LocalSearch(double** BestAreasArr, int* BestAreasSolutions, double** ForagersArr, int* ForagersSolutions, Segments segments, double** BestAreasLocalArr);
	double** NewBees(double** NewBeeArr, double** BestAreasLocalArr);
	double** algorithm(double** BeeArr, int rows, Segments segments, bool print);
};

