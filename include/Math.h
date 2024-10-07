#pragma once
#include <string>
#include <vector>

// --- Matrix operations

std::vector<std::vector<double>> operator*(std::vector<std::vector<double>>& firstMatrix,
    std::vector<std::vector<double>>& secondMatrix);  // Matrix - Matrix multiplication - overloaded operator

std::vector<std::vector<double>> multiplyMatrices(std::vector<std::vector<double>>& firstMatrix,
    std::vector<std::vector<double>>& secondMatrix); // Matrix - Matrix multiplication

std::vector<double> operator*(std::vector<std::vector<double>>& Matrix, std::vector<double>& Vector); // Matrix - Vector multiplication - overloaded operator

std::vector<double> multiplyMatrixVector(std::vector<std::vector<double>>& Matrix, std::vector<double>& Vector); // Matrix - Vector multiplication

bool randBool();
 
double randProb();

int preSort(std::vector<std::vector<double>>& orderedVector);

void quickSort(std::vector<std::vector<double>>& orderedVector, int startingPoint, int endingPoint);

int partition(std::vector<std::vector<double>>& orderedVector, int startingPoint, int endingPoint); 

std::vector<double> mtMm(std::vector<std::vector<double>>& Matrix, std::vector<double>& Vector);

