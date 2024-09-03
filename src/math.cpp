#include <string>
#include <vector>
#include <random>
#include <Math.h>
#include <iostream>
#include <thread>
#include <future>
#include "Markov.h"

// order of operation matters! M1 * M2 represents the left side multiplication of M2 to M1 and M2 * M1 the right side multiplication of M2 to M1.

std::vector<std::vector<double>> operator*(std::vector<std::vector<double>>& firstMatrix, std::vector<std::vector<double>>& secondMatrix) // Matrix - Matrix multiplication - overloaded operator    
{
    size_t m1, n1;
    size_t m2, n2;

    m1 = firstMatrix.size(); // rows
    n1 = firstMatrix[0].size(); // columns

    m2 = secondMatrix.size();
    n2 = secondMatrix[0].size();

    if (n1 != m2)
        throw 1; // Incompatible dimensions

    std::vector<std::vector<double>> result(m1, std::vector<double>(n2));

    for (size_t i = 0; i < m1; ++i) // row selection
    {
        for (size_t k = 0; k < n1; ++k) // sum over elements
        {
            for (size_t j = 0; j < n2; ++j) // column selection
            {
                result[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }

    return result;
}

std::vector<std::vector<double>> multiplyMatrices(std::vector<std::vector<double>>& firstMatrix, std::vector<std::vector<double>>& secondMatrix) // Matrix - Matrix multiplication
{
    size_t m1, n1;
    size_t m2, n2;

    m1 = firstMatrix.size(); // rows
    n1 = firstMatrix[0].size(); // columns

    m2 = secondMatrix.size();
    n2 = secondMatrix[0].size();

    if (n1 != m2)
        throw 1; // Incompatible dimensions

    std::vector<std::vector<double>> result(m1, std::vector<double>(n2));

    for (size_t i = 0; i < m1; ++i) // row selection
    {
        for (size_t k = 0; k < n1; ++k) // sum over elements
        {
            for (size_t j = 0; j < n2; ++j) // column selection
            {
                result[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }

    return result;
}

std::vector<double> operator*(std::vector<std::vector<double>>& Matrix, std::vector<double>& Vector) // Matrix - Vector multiplication - overloaded operator
{
    size_t m1, n1;
    size_t m2, n2;
    double epsilon = 1e-6;

    m1 = Matrix.size(); // rows
    n1 = Matrix[0].size(); // columns

    m2 = Vector.size();

    if (n1 != m2)
        throw 1; // Incompatible dimensions

    std::vector<double> result(m1);

    for (size_t i = 0; i < m1; ++i)
    {
        for (size_t j = 0; j < n1; ++j)
        {
            if (Vector[j] < epsilon) // abs() has been omitted for efficiency
                continue;
            result[i] += Matrix[i][j] * Vector[j];
        }
    }

    return result;
}

std::vector<double> multiplyMatrixVector(const std::vector<std::vector<double>>& Matrix, const std::vector<double>& Vector) // Matrix - Vector multiplication
{
    size_t m1, n1;
    size_t m2, n2;
    double epsilon = 1e-6;

    m1 = Matrix.size(); // rows
    n1 = Matrix[0].size(); // columns

    m2 = Vector.size();

    if (n1 != m2)
        throw 1; // Incompatible dimensions

    std::vector<double> result(m1);

    for (size_t i = 0; i < m1; ++i)
    {
        for (size_t j = 0; j < n1; ++j)
        {
            if (Vector[j] < epsilon) // abs() has been omitted for efficiency
                continue;
            result[i] += Matrix[i][j] * Vector[j];
        }
    }

    return result;
}

bool randBool()
{
    bool randomBool;
    std::random_device rd;
    std::uniform_int_distribution<> dist(0, 1);
    randomBool = dist(rd);
    return randomBool;
}

double randProb()
{
    double randomProbability;
    std::random_device rd;
    std::uniform_real_distribution<double> dist(0, 1);
    randomProbability = dist(rd);
    return randomProbability;
}

int preSort(std::vector<std::vector<double>>& orderedVector) // puts all non-zero values to the front of the vector (zero values are irrelevant for probability)
{
    size_t n = orderedVector[0].size();
    int swaps = 0;

    for (size_t i = 0; i < n; ++i)
    {
        if (orderedVector[1][i] > 0)
        {
            std::swap(orderedVector[0][i], orderedVector[0][swaps]);
            std::swap(orderedVector[1][i], orderedVector[1][swaps]);
            ++swaps;
        }
    }
    return swaps - 1; // acts as indicator where the zeros start
}

void quickSort(std::vector<std::vector<double>>& orderedVector, int startingPoint, int endingPoint)
{
    if (startingPoint >= endingPoint)
        return;

    int pivot = partition(orderedVector, startingPoint, endingPoint);
    quickSort(orderedVector, startingPoint, pivot - 1);
    quickSort(orderedVector, pivot + 1, endingPoint);

}

int partition(std::vector<std::vector<double>>& orderedVector, int startingPoint, int endingPoint)
{
    double pivot = orderedVector[1][startingPoint];
    int i = startingPoint;

    for (int j = startingPoint + 1; j <= endingPoint; ++j)
    {
        if (orderedVector[1][j] > pivot)
        {
            ++i;
            std::swap(orderedVector[1][j], orderedVector[1][i]);
            std::swap(orderedVector[0][j], orderedVector[0][i]);
        }
    }
    std::swap(orderedVector[1][startingPoint], orderedVector[1][i]);
    std::swap(orderedVector[0][startingPoint], orderedVector[0][i]);

    return i;
}

std::vector<double> mtMm(std::vector<std::vector<double>>& Matrix, std::vector<double>& Vector) //multi-thread Matrix multiplication
{
    size_t n = Matrix.size();
    size_t w1 = floor(n / 2);

    std::vector<std::vector<double>> M1(Matrix.begin(), Matrix.begin() + w1);
    std::vector<std::vector<double>> M2(Matrix.begin() + w1, Matrix.end());
    auto multiplyMatrixVectorPtr = static_cast<std::vector<double>(*)(const std::vector<std::vector<double>>&, const std::vector<double>&)>(&multiplyMatrixVector);
    Timer timer;
    std::future<std::vector<double>> fu = std::async(std::launch::async, multiplyMatrixVectorPtr, std::cref(M1), std::cref(Vector));
    std::vector<double> R2 = M2 * Vector;
    std::vector<double> R1 = fu.get(); 

    R1.insert(R1.end(), R2.begin(), R2.end());
    return R1;
}