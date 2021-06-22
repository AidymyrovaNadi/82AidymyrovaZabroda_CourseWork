#pragma once
#include "Segments.h"
#include "GeomLines.h"
#include "Rand.h"
#include "main.h"

using namespace std;

class RecordSolution
{
public:
	GeomLine optimumLine;
	int optimumVal = optimumLine.solutionVal;

	int Find(double** linesArr, int* solutions, int rows, Segments segments);
	void Print();
private:
	Rand RecordRand;
	Main RecordProg;
};
