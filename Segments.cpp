#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include "Segments.h"
#include "Rand.h"
#include "main.h"

using namespace std;

int** Segments::FromFile(string filename, int& rows, int columns)
{
    ifstream in(filename);

    if (in.is_open())
    {
        int count = 0;
        int temp;

        while (!in.eof())
        {
            in >> temp;
            count++;
        }

        in.seekg(0, ios::beg);
        in.clear();


        int count_space = 0;
        char symbol;
        while (!in.eof())
        {
            in.get(symbol);
            if (symbol == ' ') count_space++;
            if (symbol == '\n') break;
        }

        in.seekg(0, ios::beg);
        in.clear();

        rows = count / (count_space + 1);
        columns = count_space + 1;
        arr = new int* [rows];
        for (int i = 0; i < rows; i++) arr[i] = new int[columns];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                in >> arr[i][j];

        in.close();
        return arr;
    }
    else
    {
        cout << " ���� �� ��������.\n";
        exit(0);
    }
}

int** Segments::Input(int rows, int columns)
{
    arr = new int* [rows];
    for (int i = 0; i < rows; i++) arr[i] = new int[columns];

    printf("\n ����i�� ���������� �i������ ����� ��� ������� �i��i��� (4 ����� ����� ����i�, ���������, 1 12 3 6)\n\n");
    for (int i = 0; i < rows; i++)
    {
        printf(" �i��i��� �%d: ", i + 1);
        cin >> arr[i][0] >> arr[i][1] >> arr[i][2] >> arr[i][3];
    }

    return arr;
}

int** Segments::Random(int rows, int columns)
{
    this->arr = new int* [rows];
    for (int i = 0; i < rows; i++) this->arr[i] = new int[columns];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            this->arr[i][j] = SegRand.Int(0, 20);
        }
    }

    return this->arr;
}

void Segments::Print(int** arr, int rows)
{
    printf("\n �i���i��� �i��i��i�: %d.\n", rows);
    printf(" ���������� �i������ �����:\n");

    for (int i = 0; i < rows; i++)
    {
        printf(" �i��i��� �%d: (%d; %d), (%d; %d)\n", i + 1, arr[i][0], arr[i][1], arr[i][2], arr[i][3]);
    }
}