#pragma once
#include <string>
#include <vector>

// --- Matrix operations

std::vector<std::vector<float>> operator*(std::vector<std::vector<float>>& firstMatrix,
    std::vector<std::vector<float>>& secondMatrix);  // Matrix - Matrix multiplication - overloaded operator

std::vector<std::vector<float>> multiplyMatrices(std::vector<std::vector<float>>& firstMatrix,
    std::vector<std::vector<float>>& secondMatrix); // Matrix - Matrix multiplication

std::vector<float> operator*(std::vector<std::vector<float>>& Matrix, std::vector<float>& Vector); // Matrix - Vector multiplication - overloaded operator

std::vector<float> multiplyMatrixVector(std::vector<std::vector<float>>& Matrix, std::vector<float>& Vector); // Matrix - Vector multiplication