#include <string>
#include "Segments.h"
#include "GeomLines.h"
#include "RecordSolution.h"
#include "Bee.h"

using namespace std;

double** Bee::ChooseArea(double** BestAreasArr, double** BeeArr, int* BeeSolutions, int rows)
{
    BestAreasArr = BestAreas.ArrInit(m_b);

    for (int i = 0; i < rows - 1; ++i) {
        for (int j = 0; j < rows - i - 1; ++j) {
            if (BeeSolutions[j] < BeeSolutions[j + 1])
            {
                int b = BeeSolutions[j];
                BeeSolutions[j] = BeeSolutions[j + 1];
                BeeSolutions[j + 1] = b;

                BeeSolution.Program.swapRows(BeeArr[j], BeeArr[j + 1]);
            }
        }
    }

    for (int i = 0; i < m_b; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            BestAreasArr[i][j] = BeeArr[i][j];
        }
    }

    return BestAreasArr;
}

double** Bee::ForagersInit(double** ForagersArr, double** BestAreasArr)
{
    int l = 0;
    int p1 = 3, p2 = 2;
    double k1, a1;
    ForagersArr = Foragers.ArrInit(n_f);

    do
    {
        for (int i = 0; i < m_b; i++)
        {
            k1 = BestAreasArr[i][0];
            a1 = BestAreasArr[i][1];

            if (i < n_f % m_b)
            {
                for (int j = 0; j < p1; j++)
                {
                    ForagersArr[l][0] = Foragers.random.Double(k1 - r, k1 + r);
                    ForagersArr[l][1] = Foragers.random.Double(a1 - r, a1 + r);
                    l++;
                }
            }
            else
            {
                for (int j = 0; j < p2; j++)
                {
                    ForagersArr[l][0] = Foragers.random.Double(k1 - r, k1 + r);
                    ForagersArr[l][1] = Foragers.random.Double(a1 - r, a1 + r);
                    l++;
                }
            }
        }
    } while (l < n_f);

    return ForagersArr;
}

double** Bee::LocalSearch(double** BestAreasArr, int* BestAreasSolutions, double**ForagersArr, int* ForagersSolutions, Segments segments, double** BestAreasLocalArr)
{
    int l = 0;
    int p1 = 3, p2 = 2;
    int Upd = 0;
    BestAreasLocalArr = BestAreasLocal.ArrInit(m_b);

    for (int i = 0; i < m_b; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            BestAreasLocalArr[i][j] = BestAreasArr[i][j];
        }
    }

    l = 0;

    do
    {
        for (int i = 0; i < m_b; i++)
        {
            if (i < n_f % m_b)
            {
                for (int j = 0; j < p1; j++)
                {
                    if (ForagersSolutions[l] > BestAreasSolutions[i])
                    {
                        for (int k = 0; k < 2; k++)
                        {
                            BestAreasLocalArr[i][k] = ForagersArr[l][k];
                        }
                        Upd++;
                    }
                    l++;
                }
            }
            else
            {
                for (int j = 0; j < p2; j++)
                {
                    if (ForagersSolutions[l] > BestAreasSolutions[i])
                    {
                        for (int k = 0; k < 2; k++)
                        {
                            BestAreasLocalArr[i][k] = ForagersArr[l][k];
                        }
                        Upd++;
                    }
                    l++;
                }
            }
        }

    } while (l < n_f);

    return BestAreasLocalArr;
}

double** Bee::NewBees(double** NewBeeArr, double** BestAreasLocalArr)
{
    int newRows = n_s - m_b;

    NewBeeArr = BeeSolution.ArrFill(n_s);

    for (int i = 0; i < m_b; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            NewBeeArr[i + newRows][j] = BestAreasLocalArr[i][j];
        }
    }

    return NewBeeArr;
}

double** Bee::algorithm(double** BeeArr, int rows, Segments segments, bool print)
{
    int* beeSolutions = BeeSolution.solutions;
    beeSolutions = BeeSolution.IntersectionArr(BeeArr, rows, segments);

    if (print)
    {
        printf("\n\n Бджоли-розвiдники:");
        BeeSolution.PrintTable(BeeArr, rows, beeSolutions);
    }

    double** bestAreasArr = BestAreas.linesArr;
    bestAreasArr = ChooseArea(bestAreasArr, BeeArr, beeSolutions, rows);
    int* bestAreasSolutions = BestAreas.solutions;
    bestAreasSolutions = BestAreas.IntersectionArr(bestAreasArr, m_b, segments);

    if (print)
    {
        printf("\n\n Найкращi дiлянки:");
        BestAreas.PrintTable(bestAreasArr, m_b, bestAreasSolutions);
    }

    double** ForagersArr = Foragers.linesArr;
    ForagersArr = ForagersInit(ForagersArr, bestAreasArr);
    int* ForagersSolutions = Foragers.solutions;
    ForagersSolutions = Foragers.IntersectionArr(ForagersArr, n_f, segments);

    if (print)
    {
        printf("\n\n Бджоли-фуражири:");
        Foragers.PrintTable(ForagersArr, n_f, ForagersSolutions);
    }

    double** bestAreasLocalArr = BestAreasLocal.linesArr;
    bestAreasLocalArr = LocalSearch(bestAreasArr, bestAreasSolutions, ForagersArr, ForagersSolutions, segments, bestAreasLocalArr);
    int* bestAreasLocalSolutions = BestAreasLocal.solutions;
    bestAreasLocalSolutions = BestAreasLocal.IntersectionArr(bestAreasLocalArr, m_b, segments);

    if (print)
    {
        printf("\n\n Перемiщення:");
        BestAreasLocal.PrintTable(bestAreasLocalArr, m_b, bestAreasLocalSolutions);
    }

    optimum.Find(bestAreasLocalArr, bestAreasLocalSolutions, m_b, segments);
    if (print) optimum.Print();

    double** NewBeeArr = BeeSolution.linesArr;
    NewBeeArr = NewBees(NewBeeArr, bestAreasLocalArr);
    int* NewBeeSolutions = BeeSolution.solutions;
    NewBeeSolutions = BeeSolution.IntersectionArr(NewBeeArr, rows, segments);

    if (print)
    {
        printf("\n\n Новi бджоли-розвiдники:");
        BeeSolution.PrintTable(NewBeeArr, rows, NewBeeSolutions);
    }

    return NewBeeArr;
}