#pragma once
#include <string>
#include "Rand.h"
#include "main.h"

using namespace std;

class Segments
{
public:
	static const int columns = 4;
	int rows;
	string filename = "segments.txt";
	int** arr;

	int** FromFile(string filename, int& rows, int columns);
	int** Random(int rows, int columns);
	int** Input(int rows, int columns);

	void Print(int** arr, int rows);
private:
	Rand SegRand;
	Main SegProg;
};

