#include <iostream>
#include <omp.h>
#include <chrono>
using namespace std;

#define N 10000

int matrix1[N][N];
int matrix2[N][N];
int matrixOfMulti[N][N];
void SingleThreadMultiplication()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int summ = 0;
            for (int k = 0; k < N; k++)
            {
                summ += matrix1[i][j] * matrix2[k][j];
            }
            matrixOfMulti[i][j] = summ;
        }
    }
}

void MultiThreadMultiplication()
{
    #pragma omp parallel for private(i,j,k) shared(matrix1, matrix2, matrixOfMulti)
    for (int i = 0; i < N; i++)
    {
        
        for (int j = 0; j < N; j++)
        {
            int summ = 0;
            for (int k = 0; k < N; k++)
            {
                summ += matrix1[i][j] * matrix2[k][j];
            }
            matrixOfMulti[i][j] = summ;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix1[i][j] = rand();
            matrix2[i][j] = rand();
        }
    }
    auto start = std::chrono::steady_clock::now();
    //SingleThreadMultiplication();
    MultiThreadMultiplication();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}


