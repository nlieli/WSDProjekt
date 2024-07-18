#include <string>
#include <vector>
#include <random>
#include <Math.h>

// order of operation matters! M1 * M2 represents the left side multiplication of M2 to M1 and M2 * M1 the right side multiplication of M2 to M1.

std::vector<std::vector<float>> operator*(std::vector<std::vector<float>>& firstMatrix, std::vector<std::vector<float>>& secondMatrix) // Matrix - Matrix multiplication - overloaded operator    
{
    size_t m1, n1;
    size_t m2, n2;

    m1 = firstMatrix.size(); // rows
    n1 = firstMatrix[0].size(); // columns

    m2 = secondMatrix.size();
    n2 = secondMatrix[0].size();

    if (n1 != m2)
        throw 1; // Incompatible dimensions

    std::vector<std::vector<float>> result(m1, std::vector<float>(n2));

    for (size_t i = 0; i < m1; ++i) // row selection
    {
        for (size_t j = 0; j < n2; ++j) // column selection
        {
            for (size_t k = 0; k < n1; ++k) // sum over elements
            {
                result[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }

    return result;
}

std::vector<std::vector<float>> multiplyMatrices(std::vector<std::vector<float>>& firstMatrix, std::vector<std::vector<float>>& secondMatrix) // Matrix - Matrix multiplication
{
    size_t m1, n1;
    size_t m2, n2;

    m1 = firstMatrix.size(); // rows
    n1 = firstMatrix[0].size(); // columns

    m2 = secondMatrix.size();
    n2 = secondMatrix[0].size();

    if (n1 != m2)
        throw 1; // Incompatible dimensions

    std::vector<std::vector<float>> result(m1, std::vector<float>(n2));

    for (size_t i = 0; i < m1; ++i) // row selection
    {
        for (size_t j = 0; j < n2; ++j) // column selection
        {
            for (size_t k = 0; k < n1; ++k) // sum over elements
            {
                result[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }

    return result;
}

std::vector<float> operator*(std::vector<std::vector<float>>& Matrix, std::vector<float>& Vector) // Matrix - Vector multiplication - overloaded operator
{
    size_t m1, n1;
    size_t m2, n2;

    m1 = Matrix.size(); // rows
    n1 = Matrix[0].size(); // columns

    m2 = Vector.size();

    if (n1 != m2)
        throw 1; // Incompatible dimensions

    std::vector<float> result(m1);

    for (size_t i = 0; i < m1; ++i)
    {
        for (size_t j = 0; j < n1; ++j)
        {
            result[i] += Matrix[i][j] * Vector[j];
        }
    }

    return result;
}

std::vector<float> multiplyMatrixVector(std::vector<std::vector<float>>& Matrix, std::vector<float>& Vector) // Matrix - Vector multiplication
{
    size_t m1, n1;
    size_t m2, n2;

    m1 = Matrix.size(); // rows
    n1 = Matrix[0].size(); // columns

    m2 = Vector.size();

    if (n1 != m2)
        throw 1; // Incompatible dimensions

    std::vector<float> result(m1);

    for (size_t i = 0; i < m1; ++i) 
    {
        for (size_t j = 0; j < n1; ++j)
        {
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

float randProb()
{
    float randomProbability;
    std::random_device rd;
    std::uniform_real_distribution<float> dist(0, 1);
    randomProbability = dist(rd);
    return randomProbability;
}

void renSort(std::vector<std::vector<float>>& orderedVector) // --- randomize equal numbers sort
{
    size_t n = orderedVector[0].size();
    bool swapped;

    do { // --- modified bubblesort algorithm
        swapped = false;
        n--;

        for (size_t i = 0; i < n; ++i)
        {
            if (orderedVector[1][i] < orderedVector[1][i + 1])
            {
                swapped = true;
                std::swap(orderedVector[0][i], orderedVector[0][i + 1]);
                std::swap(orderedVector[1][i], orderedVector[1][i + 1]);
            }
            else if ((orderedVector[1][i] == orderedVector[1][i + 1]) && randBool() && (orderedVector[1][i] != 0))

            {
                std::swap(orderedVector[0][i], orderedVector[0][i + 1]);
                std::swap(orderedVector[1][i], orderedVector[1][i + 1]);
            }
        }

    } while (swapped);
}

int preSort(std::vector<std::vector<float>>& orderedVector) // puts all non-zero values to the front of the vector (zero values are irrelevant for probability)
{
    size_t n = orderedVector.size();
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
    return swaps; // acts as indicator where the zeros start
}

void quickSort(std::vector<std::vector<float>>& orderedVector, int startingPoint, int endingPoint)
{
    if (startingPoint <= endingPoint)
        return;

    int pivot = partition(orderedVector, startingPoint, endingPoint);
    quickSort(orderedVector, startingPoint, pivot - 1);
    quickSort(orderedVector, pivot + 1, endingPoint);

}

int partition(std::vector<std::vector<float>>& orderedVector, int startingPoint, int endingPoint) 
 {
    int pivot = orderedVector[1][endingPoint];
    int i = startingPoint - 1;

    for (int j = startingPoint; j <= endingPoint - 1; ++j)
    {
        if (orderedVector[1][j] < pivot)
        {
            ++i;
            std::swap(orderedVector[1][j], orderedVector[1][i]);
            std::swap(orderedVector[0][j], orderedVector[0][i]);
        }
    }
    ++i;
    std::swap(orderedVector[1][endingPoint], orderedVector[1][i]);
    std::swap(orderedVector[0][endingPoint], orderedVector[0][i]);

    return i;
 }
