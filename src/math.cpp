#include <string>
#include <vector>
#include <random>

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

    for (size_t i = 0; i < m1; i++) // row selection
    {
        for (size_t j = 0; j < n2; j++) // column selection
        {
            for (size_t k = 0; k < n1; k++) // sum over elements
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

    for (size_t i = 0; i < m1; i++) // row selection
    {
        for (size_t j = 0; j < n2; j++) // column selection
        {
            for (size_t k = 0; k < n1; k++) // sum over elements
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

    for (size_t i = 0; i < m1; i++)
    {
        for (size_t j = 0; j < n1; j++)
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

    for (size_t i = 0; i < m1; i++) 
    {
        for (size_t j = 0; j < n1; j++)
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

void renSort(std::vector<std::vector<float>>& orderedVector) // --- randomize equal numbers sort
{
    size_t n = orderedVector.size();
    bool swapped;

    do { // --- modified bubblesort algorithm
        swapped = false;
        n--;

        for (size_t i = 0; i < n; i++)
        {
            if (orderedVector[i][1] > orderedVector[i + 1][1])
            {
                swapped = true;
                std::swap(orderedVector[i], orderedVector[i + 1]);
            }
            else if ((orderedVector[i][1] == orderedVector[i + 1][1]) && randBool())
            {
                std::swap(orderedVector[i], orderedVector[i + 1]);
            }
        }

    } while (swapped);
}

