#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>

#include "Segments.h"
#include "Greedy.h"
#include "Genetic.h"
#include "Bee.h"
#include "RecordSolution.h"
#include "main.h"

using namespace std;

Main GlobalProgram;
Rand GlobalRandom;

int** SegmentsInit(char, int&, int);
int** SegmentsFunc(int&, int);
void Experiments();
void GeneticExperiments(char key, ofstream& file);
void BeeExperiments(char key, ofstream& file);

Segments segments;
int** SegmentsArr = segments.arr;

Greedy greedy;
Genetic geneticAlg;
Bee bee;

int main()
{
    setlocale(0, "");
    srand(static_cast<unsigned int>(time(0)));
    system("color f0");
    char key;
    int iter;
    
    if (!SegmentsArr)
    {
        SegmentsArr = SegmentsFunc(segments.rows, segments.columns);
    }
    
    while (true)
    {
        system("cls");

        printf("\t\tПОШУК РIВНЯННЯ ПРЯМОЇ, ЩО ПЕРЕТИНАЄ НАЙБIЛЬШУ КIЛЬКIСТЬ ВIДРIЗКIВ\n\n");

        printf(" Оберiть опцiю:\n 1. Задати нову множину вiдрiзкiв (IЗ).\n ");
        printf("2. Вивести множину заданих вiдрiзкiв (IЗ).\n ");
        printf("3. Рiшення задачi жадiбним алгоритмом.\n ");
        printf("4. Рiшення задачi генетичним алгоритмом.\n ");
        printf("5. Рiшення задачi бджолиним алгоритмом.\n ");
        printf("6. Результати проведення експериментiв.\n ");
        printf("0. Вихiд.\n\n Введiть номер пункту: ");

        cin >> key;

        switch (key)
        {
        case '1':
        {
            SegmentsFunc(segments.rows, segments.columns);
            break;
        }
        case '2':
        {
            segments.Print(SegmentsArr, segments.rows);
            printf("\n\n Далi [Enter]");
            _getch();
            break;
        }
        case '3':
        {
            system("cls");
            printf("\t\tПОШУК РIВНЯННЯ ПРЯМОЇ, ЩО ПЕРЕТИНАЄ НАЙБIЛЬШУ КIЛЬКIСТЬ ВIДРIЗКIВ\n");
            printf("\t\t\t\t\tЖАДIБНИЙ АЛГОРИТМ\n");

            printf("\n Введiть кiлькiсть розв'язкiв (рiвнянь прямої), яку необхiдно згенерувати (наприклад, 20): ");
            cin >> greedy.GreedySolutions.rows;

            printf("\n Кiлькiсть розв'язкiв (рiвнянь прямої): %d.", greedy.GreedySolutions.rows);
            printf("\n Кiлькiсть вiдрiзкiв: %d.\n", segments.rows);
            greedy.algorithm(greedy.GreedySolutions.rows, segments);

            printf("\n\n Далi [Enter]");
            _getch();
            break;
        }
        case '4':
        {
            int n = 0;

            system("cls");
            printf("\t\tПОШУК РIВНЯННЯ ПРЯМОЇ, ЩО ПЕРЕТИНАЄ НАЙБIЛЬШУ КIЛЬКIСТЬ ВIДРIЗКIВ\n");
            printf("\t\t\t\t\tГЕНЕТИЧНИЙ АЛГОРИТМ\n");

            printf("\n Введiть кiлькiсть розв'язкiв (рiвнянь прямої), яку необхiдно згенерувати (наприклад, 10): ");
            cin >> geneticAlg.GeneticSolution.rows;

            printf(" Введiть кiлькiсть iтерацiй (наприклад, 3): ");
            cin >> iter;
            double** geneticLinesArr = geneticAlg.GeneticSolution.linesArr;
            geneticLinesArr = geneticAlg.GeneticSolution.ArrFill(geneticAlg.GeneticSolution.rows);

            do
            {
                system("cls");
                printf("\t\tПОШУК РIВНЯННЯ ПРЯМОЇ, ЩО ПЕРЕТИНАЄ НАЙБIЛЬШУ КIЛЬКIСТЬ ВIДРIЗКIВ\n");
                printf("\t\t\t\t\tГЕНЕТИЧНИЙ АЛГОРИТМ\n");
                printf("\t\t\t\t\t    IТЕРАЦIЯ %d", n + 1);

                printf("\n Кiлькiсть розв'язкiв (рiвнянь прямої): %d.", geneticAlg.GeneticSolution.rows);
                printf("\n Кiлькiсть вiдрiзкiв: %d.\n", segments.rows);

                geneticLinesArr = geneticAlg.algorithm(geneticLinesArr, geneticAlg.GeneticSolution.rows, segments, true);

                printf("\n\n Далi [Enter]");
                _getch();

                n++;
            } while (n < iter);

            break;
        }
        case '5':
        {
            int n = 0;

            system("cls");
            printf("\t\tПОШУК РIВНЯННЯ ПРЯМОЇ, ЩО ПЕРЕТИНАЄ НАЙБIЛЬШУ КIЛЬКIСТЬ ВIДРIЗКIВ\n");
            printf("\t\t\t\t\tБДЖОЛИНИЙ АЛГОРИТМ\n\n");

            printf(" Введiть кiлькiсть бджiл-розвiдникiв (n_s, наприклад, 10): ");
            cin >> bee.n_s;

            printf(" Введiть кiлькiсть \"елiтних\" розв'зкiв для дослiдження (m_b, наприклад, 5): ");
            cin >> bee.m_b;

            printf(" Введiть кiлькiсть бджiл-фуражирiв (n_f, наприклад, 12): ");
            cin >> bee.n_f;

            printf(" Введiть розмiр околу для локального пошуку (r, наприклад, 5): ");
            cin >> bee.r;

            if (bee.n_f < bee.m_b)
            {
               printf("\n Помилка!\n Кiлькiсть бджiл-фуражирiв має бути бiльша за кiлькiсть \"елiтних\" розв'зкiв.\n Введiть кiлькiсть бджiл-фуражирiв повторно: ");
               cin >> bee.n_f;
            }

            printf("\n Введiть кiлькiсть iтерацiй (наприклад, 3): ");
            cin >> iter;

            double** BeeArr = bee.BeeSolution.linesArr;
            BeeArr = bee.BeeSolution.ArrFill(bee.n_s);

            do
            {
                system("cls");
                printf("\t\tПОШУК РIВНЯННЯ ПРЯМОЇ, ЩО ПЕРЕТИНАЄ НАЙБIЛЬШУ КIЛЬКIСТЬ ВIДРIЗКIВ\n");
                printf("\t\t\t\t\tБДЖОЛИНИЙ АЛГОРИТМ\n\n");
                printf("\t\t\t\t\t    IТЕРАЦIЯ %d", n + 1);

                printf("\n\n Кiлькiсть бджiл-розвiдникiв: %d.\n Кiлькiсть \"елiтних\" розв'зкiв для дослiдження: %d.\n Кiлькiсть бджiл-фуражирiв: %d.\n Розмiр околу для локального пошуку: %d.\n\n", bee.n_s, bee.m_b, bee.n_f, bee.r);
                printf("\n Кiлькiсть вiдрiзкiв: %d.\n", segments.rows);

                BeeArr = bee.algorithm(BeeArr, bee.n_s, segments, true);

                printf("\n\n Далi [Enter]");
                _getch();

                n++;
            } while (n < iter);

            break;
        }
        case '6': 
        {
            system("cls");
            printf("\t\tПОШУК РIВНЯННЯ ПРЯМОЇ, ЩО ПЕРЕТИНАЄ НАЙБIЛЬШУ КIЛЬКIСТЬ ВIДРIЗКIВ\n");
            printf("\t\t\t\t\tЕКСПЕРИМЕНТИ\n\n");

            Experiments();

            printf("\n\n Далi [Enter]");
            _getch();
            break;
        }
        case '0':
        {
            exit(0);
        }
        default:
            printf("\n Такої опцiї немає. Спробуйте ще раз.");
            _getch();
            break;
        }
    }

}

int** SegmentsInit(char key, int& rows, int columns)
{
    system("cls");
    printf("\t\tПОШУК РIВНЯННЯ ПРЯМОЇ, ЩО ПЕРЕТИНАЄ НАЙБIЛЬШУ КIЛЬКIСТЬ ВIДРIЗКIВ\n");
    printf("\t\t\t\tIНIЦIАЛIЗАЦIЯ ВIДРIЗКIВ ");

    string filename = segments.filename;

    switch (key)
    {
    case '1':
        printf("(ФАЙЛ)\n\n Введiть iм'я файлу (наприклад, segments.txt): ");
        cin >> filename;
        SegmentsArr = segments.FromFile(filename, rows, columns);
        break;
    case '2':
        printf("(ВВЕДЕННЯ)\n\n Введiть кiлькiсть вiдрiзкiв (наприклад, 15): ");
        cin >> rows;
        SegmentsArr = segments.Input(rows, columns);
        break;
    case '3':
        printf("(ВИПАДКОВИМ ЧИНОМ)\n\n Введiть кiлькiсть вiдрiзкiв (наприклад, 15): ");
        cin >> rows;
        SegmentsArr = segments.Random(rows, columns);
        break;
    default:
        break;
    }

    segments.Print(SegmentsArr, rows);

    //_getch();
    return SegmentsArr;
}

int** SegmentsFunc(int& rows, int columns)
{
    char key;																		                // variable for menu

    system("cls");
    printf("\t\tПОШУК РIВНЯННЯ ПРЯМОЇ, ЩО ПЕРЕТИНАЄ НАЙБIЛЬШУ КIЛЬКIСТЬ ВIДРIЗКIВ\n\n");
    printf(" Для початку роботи програми, необхiдно задати вiдрiзки на площинi:\n");
    printf(" 1. Зчитати координати вiдрiзкiв з файлу.\n");
    printf(" 2. Ввести координати вiдрiзкiв вручну.\n");
    printf(" 3. Згенерувати координати вiдрiзкiв випадковим чином.\n");
    printf(" 0. Вихiд.\n");

    printf("\n Введiть номер пункту: ");

    cin >> key;

    switch (key)
    {
    case '1':
    {
        SegmentsArr = SegmentsInit('1', rows, columns);					                            // reading segments from file
        break;
    }
    case '2':
    {
        SegmentsArr = SegmentsInit('2', rows, columns);												// input segments
        break;
    }
    case '3':
    {
        SegmentsArr = SegmentsInit('3', rows, columns);												// rand segments
        break;
    }
    case '0':
    {
        exit(0);
    }
    default:
        printf("\n Такої опцiї немає. Спробуйте ще раз.");
        SegmentsFunc(rows, columns);
        break;
    }

    printf("\n\n Далi [Enter]");
    _getch();

    return SegmentsArr;
}

void Experiments()
{
    int iter0 = 0, iter = 3;
    char key;

    ofstream resultExp1("resultExp1.txt");
    ofstream resultExp2("resultExp2.txt");
    ofstream resultExp3("resultExp3.txt");
    ofstream resultExp4("resultExp4.txt");
    
    while (true)
    {
        system("cls");
        printf("\t\tПОШУК РIВНЯННЯ ПРЯМОЇ, ЩО ПЕРЕТИНАЄ НАЙБIЛЬШУ КIЛЬКIСТЬ ВIДРIЗКIВ\n");
        printf("\t\t\t\t\tЕКСПЕРИМЕНТИ\n\n");

        printf(" Оберiть опцiю:\n 1. Генетичний алгоритм (за розмiрнiстю задачi).\n ");
        printf("2. Генетичний алгоритм (за розмiрнiстю початкової популяцiї).\n ");
        printf("3. Бджолиний алгоритм (за розмiрнiстю задачi).\n ");
        printf("4. Бджолиний алгоритм (за розмiром околу).\n ");
        printf("0. Назад.\n\n Введiть номер пункту: ");

        cin >> key;

        switch (key)
        {
        case '1':
        {
            GeneticExperiments('1', resultExp1);
            break;
        }
        case '2':
        {
            GeneticExperiments('2', resultExp2);
            break;
        }
        case '3':
        {
            BeeExperiments('1', resultExp3);
            break;
        }
        case '4':
        {
            BeeExperiments('2', resultExp4);
            break;
        }
        case '0':
        {
            main();
            break;
        }
        default:
            printf("\n Такої опцiї немає. Спробуйте ще раз.");
            _getch();
            break;
        }
    }
  
}

void GeneticExperiments(char key, ofstream& file)
{
    int iter0 = 0, iter = 3;

    geneticAlg.GeneticSolution.rows = 15;
    double** geneticLinesArr = geneticAlg.GeneticSolution.linesArr;
    geneticLinesArr = geneticAlg.GeneticSolution.ArrFill(geneticAlg.GeneticSolution.rows);

    switch (key)
    {
    case '1':
    {
        system("cls");
        printf("\t\tПОШУК РIВНЯННЯ ПРЯМОЇ, ЩО ПЕРЕТИНАЄ НАЙБIЛЬШУ КIЛЬКIСТЬ ВIДРIЗКIВ\n");
        printf("\t\t\t\t\tЕКСПЕРИМЕНТ 1\n\n");

        printf(" Генетичний алгоритм (за розмiрнiстю задачi)\n Вiд: %d; До: %d; Крок: %d; Iтерацiй: %d.\n", 10, 40, 5, iter);

        file << " 1. Генетичний алгоритм (за розмiрнiстю задачi)\n Вiд: " << 10 << "; До: " << 40 << "; Крок: " << 5 << "; Iтерацiй: " << iter << ".\n";

        iter0 = 0;

        for (int i = 10; i <= 40; i = i + 5)
        {
            segments.rows = i;
            segments.Random(segments.rows, segments.columns);

            auto t1 = chrono::steady_clock().now();
            do
            {
                geneticLinesArr = geneticAlg.algorithm(geneticLinesArr, geneticAlg.GeneticSolution.rows, segments, 0);
                iter0++;
            } while (iter0 < iter);
            auto t2 = chrono::steady_clock().now();

            auto time = static_cast<double>((t2 - t1).count()) / 1'000'000'000;

            printf("\n Розмiрнiсть задачi: %d; Значення ЦФ: %d; Час виконання: %f секунди.", i, geneticAlg.optimum.optimumVal, time);
            
            file << "\n Розмiрнiсть задачi: " << i << "; Значення ЦФ: " << geneticAlg.optimum.optimumVal << "; Час виконання: " << time << " секунди.";
        
        }
        printf("\n\n Далi [Enter]");
        _getch();
        break;
    }
    case '2':
    {
        system("cls");
        printf("\t\tПОШУК РIВНЯННЯ ПРЯМОЇ, ЩО ПЕРЕТИНАЄ НАЙБIЛЬШУ КIЛЬКIСТЬ ВIДРIЗКIВ\n");
        printf("\t\t\t\t\tЕКСПЕРИМЕНТ 2\n\n");

        printf(" Генетичний алгоритм (за розмiрнiстю початкової популяцiї)\n Вiд: %d; До: %d; Крок: %d; Iтерацiй: %d.\n", 10, 80, 5, iter);

        file << "\n\n 2. Генетичний алгоритм (за розмiрнiстю початкової популяцiї)\n Вiд: " << 10 << "; До: " << 80 << "; Крок: " << 5 << "; Iтерацiй: " << iter << ".\n";

        iter0 = 0;

        for (int i = 10; i <= 40; i = i + 5)
        {
            segments.rows = i;
            segments.Random(segments.rows, segments.columns);

            for (int j = 10; j <= 80; j = j + 5)
            {
                geneticAlg.GeneticSolution.rows = j;
                geneticLinesArr = geneticAlg.GeneticSolution.ArrFill(geneticAlg.GeneticSolution.rows);

                auto t1 = chrono::steady_clock().now();
                do
                {
                    geneticLinesArr = geneticAlg.algorithm(geneticLinesArr, geneticAlg.GeneticSolution.rows, segments, 0);
                    iter0++;
                } while (iter0 < iter);
                auto t2 = chrono::steady_clock().now();

                auto time = static_cast<double>((t2 - t1).count()) / 1'000'000'000;

                printf("\n Розмiрнiсть задачi: %d; Розмiрнiсть початкової популяцiї: %d; Значення ЦФ: %d; Час виконання: %f секунди.", i, geneticAlg.GeneticSolution.rows, geneticAlg.optimum.optimumVal, time);
                
                file << "\n Розмiрнiсть задачi: " << i << "; Розмiрнiсть початкової популяцiї: " << geneticAlg.GeneticSolution.rows << "; Значення ЦФ: " << geneticAlg.optimum.optimumVal << "; Час виконання: " << time << " секунди.";
                
            }
        }
        printf("\n\n Далi [Enter]");
        _getch();
        break;
    }
    default:
        break;
    }
}

void BeeExperiments(char key, ofstream& file)
{
    int iter0 = 0, iter = 3;

    bee.n_s = 10, bee.m_b = 5, bee.n_f = 12, bee.r = 5;
    double** BeeArr = bee.BeeSolution.linesArr;
    BeeArr = bee.BeeSolution.ArrFill(bee.n_s);

    switch (key)
    {
    case '1':
    {
        system("cls");
        printf("\t\tПОШУК РIВНЯННЯ ПРЯМОЇ, ЩО ПЕРЕТИНАЄ НАЙБIЛЬШУ КIЛЬКIСТЬ ВIДРIЗКIВ\n");
        printf("\t\t\t\t\tЕКСПЕРИМЕНТ 3\n\n");
        printf(" Бджолиний алгоритм (за розмiрнiстю задачi)\n Вiд: %d; До: %d; Крок: %d; Iтерацiй: %d.\n", 10, 40, 5, iter);

        file << "\n\n 3. Бджолиний алгоритм (за розмiрнiстю задачi)\n Вiд: " << 10 << "; До: " << 40 << "; Крок: " << 5 << "; Iтерацiй: " << iter << ".\n";

        for (int i = 10; i <= 40; i = i + 5)
        {
            segments.rows = i;
            segments.Random(segments.rows, segments.columns);

            auto t1 = chrono::steady_clock().now();
            do
            {
                BeeArr = bee.algorithm(BeeArr, bee.n_s, segments, 0);
                iter0++;
            } while (iter0 < iter);
            auto t2 = chrono::steady_clock().now();

            auto time = static_cast<double>((t2 - t1).count()) / 1'000'000'000;

            printf("\n Розмiрнiсть задачi: %d; Значення ЦФ: %d; Час виконання: %f секунди.", i, bee.optimum.optimumVal, time);

            file << "\n Розмiрнiсть задачi: " << i << "; Значення ЦФ: " << bee.optimum.optimumVal << "; Час виконання: " << time << " секунди.";

        }
        printf("\n\n Далi [Enter]");
        _getch();
        break;
    }
    case '2':
    {
        system("cls");
        printf("\t\tПОШУК РIВНЯННЯ ПРЯМОЇ, ЩО ПЕРЕТИНАЄ НАЙБIЛЬШУ КIЛЬКIСТЬ ВIДРIЗКIВ\n");
        printf("\t\t\t\t\tЕКСПЕРИМЕНТ 4\n\n");
        printf(" Бджолиний алгоритм (за розмiром околу)\n Вiд: %d; До: %d; Крок: %d; Iтерацiй: %d.\n", 5, 30, 2, iter);

        file << "\n\n 4. Бджолиний алгоритм (за розмiром околу)\n Вiд: " << 5 << "; До: " << 30 << "; Крок: " << 2 << "; Iтерацiй: " << iter << ".\n";
        
        for (int i = 10; i <= 40; i = i + 5)
        {
            segments.rows = i;
            segments.Random(segments.rows, segments.columns);

            for (int j = 5; j <= 20; j = j + 2)
            {
                bee.r = j;

                auto t1 = chrono::steady_clock().now();
                do
                {
                    BeeArr = bee.algorithm(BeeArr, bee.n_s, segments, 0);
                    iter0++;
                } while (iter0 < iter);
                auto t2 = chrono::steady_clock().now();

                auto time = static_cast<double>((t2 - t1).count()) / 1'000'000'000;

                printf("\n Розмiрнiсть задачi: %d; Розмiр околу: %d; Значення ЦФ: %d; Час виконання: %f секунди.", i, bee.r, bee.optimum.optimumVal, time);

                file << "\n Розмiрнiсть задачi: " << i << "; Розмiр околу: " << bee.r << "; Значення ЦФ: " << bee.optimum.optimumVal << "; Час виконання: " << time << " секунди.";
            }
            
        }
        printf("\n\n Далi [Enter]");
        _getch();
        break;
    }
    default:
        break;
    }
}