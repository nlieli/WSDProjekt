#include <string>
#include <vector>

// order of operation matters! M1 * M2 represents the left side multiplication of M2 to M1 and M2 * M1 the right side multiplication of M2 to M1.

std::vector<std::vector<int>> operator*(std::vector<std::vector<int>> firstMatrix, std::vector<std::vector<int>> secondMatrix) // Matrix - Matrix multiplication - overloaded operator    
{
    int m1, n1;
    int m2, n2;

    m1 = firstMatrix.size(); // rows
    n1 = firstMatrix[0].size(); // columns

    m2 = secondMatrix.size();
    n2 = secondMatrix[0].size();

    if (n1 != m2)
        throw 1; // Incompatible dimensions

    std::vector<std::vector<int>> result(m1, std::vector<int>(n2));

    for (int i = 0; i < m1; i++) // row selection
    {
        for (int j = 0; j < n2; j++) // column selection
        {
            for (int k = 0; k < n1; k++) // sum over elements
            {
                result[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }

    return result;
}

std::vector<std::vector<int>> multiplyMatrices(std::vector<std::vector<int>> firstMatrix, std::vector<std::vector<int>> secondMatrix) // Matrix - Matrix multiplication
{
    int m1, n1;
    int m2, n2;

    m1 = firstMatrix.size(); // rows
    n1 = firstMatrix[0].size(); // columns

    m2 = secondMatrix.size();
    n2 = secondMatrix[0].size();

    if (n1 != m2)
        throw 1; // Incompatible dimensions

    std::vector<std::vector<int>> result(m1, std::vector<int>(n2));

    for (int i = 0; i < m1; i++) // row selection
    {
        for (int j = 0; j < n2; j++) // column selection
        {
            for (int k = 0; k < n1; k++) // sum over elements
            {
                result[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }

    return result;
}

std::vector<int> operator*(std::vector<std::vector<int>> Matrix, std::vector<int> Vector) // Matrix - Vector multiplication - overloaded operator
{
    int m1, n1;
    int m2, n2;

    m1 = Matrix.size(); // rows
    n1 = Matrix[0].size(); // columns

    m2 = Vector.size();

    if (n1 != m2)
        throw 1; // Incompatible dimensions

    std::vector<int> result(m1);

    for (int i = 0; i < m1; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            result[i] += Matrix[i][j] * Vector[j];
        }
    }

    return result;
}

std::vector<int> multiplyMatrixVector(std::vector<std::vector<int>> Matrix, std::vector<int> Vector) // Matrix - Vector multiplication
{
    int m1, n1;
    int m2, n2;

    m1 = Matrix.size(); // rows
    n1 = Matrix[0].size(); // columns

    m2 = Vector.size();

    if (n1 != m2)
        throw 1; // Incompatible dimensions

    std::vector<int> result(m1);

    for (int i = 0; i < m1; i++) 
    {
        for (int j = 0; j < n1; j++)
        {
            result[i] += Matrix[i][j] * Vector[j];
        }
    }

    return result;
}