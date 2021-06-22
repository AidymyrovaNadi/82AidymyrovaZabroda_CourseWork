#pragma once
#include <string>
#include "Segments.h"
#include "Rand.h"
#include "main.h"

using namespace std;

class GeomLines
{
public:
	int rows;
	static const int columns = 2;
	double** linesArr;
	int* solutions;

	Rand random;
	Main Program;

	double** ArrInit(int& rows);
	double** ArrFill(int& rows);

	int* IntersectionArr(double** linesArr, int rows, Segments segments);
	void PrintSolutions(double** linesArr, int rows, int* solutions);
	void PrintTable(double** linesArr, int rows, int* solutions);
};

class GeomLine
{	
	const int rows = 1;
	int columns = 2;
public:	
	double k = 0;
	double A = 0;
	double* line = new double[columns];
	int solutionVal = 0;

	Rand random;
	Main Program;

	double* LineInit();
	double* LineFill();

	void EquationOutput(double k, double A);
	int Intersection(double k, double A, Segments segments);
	void PrintSolution();
};

