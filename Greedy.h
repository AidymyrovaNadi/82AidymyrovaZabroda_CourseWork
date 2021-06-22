#pragma once
#include <string>
#include "Segments.h"
#include "GeomLines.h"
#include "RecordSolution.h"

using namespace std;

class Greedy
{
public:
	int rows;
	GeomLines GreedySolutions;
	RecordSolution optimum;

	double** InitSolutions(int& rows);
	void algorithm(int rows, Segments segments);
};
