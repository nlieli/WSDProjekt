#pragma once
#include <string>
#include <vector>

// --- Matrix operations

std::vector<std::vector<int>> operator*(std::vector<std::vector<int>> firstMatrix,
    std::vector<std::vector<int>> secondMatrix);  // Matrix - Matrix multiplication - overloaded operator

std::vector<std::vector<int>> multiplyMatrices(std::vector<std::vector<int>> firstMatrix,
    std::vector<std::vector<int>> secondMatrix); // Matrix - Matrix multiplication

std::vector<int> operator*(std::vector<std::vector<int>> Matrix, std::vector<int> Vector); // Matrix - Vector multiplication - overloaded operator

std::vector<int> multiplyMatrixVector(std::vector<std::vector<int>> Matrix, std::vector<int> Vector); // Matrix - Vector multiplication