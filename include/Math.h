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

// --- Random
/*
renSort stands for randomize equal numbers sort - it sorts a vector that has its index stored in the row 0
this preserves the information about the initial order - this is specifically needed to find the largest values
while still being able to reference those values to the corresponding string later. 

At the same time, it randomizes the positions of equal values with respect to each other. This is needed because
later on, the probability stored in a the columns of the Markov Matrix are going to be compared to a random 
number to determine the actual suggestion of the algorithm - this happens using random_number < matrix_prob_value.
If random_number is smaller than that value, which comes from an ordered list of all probabilites, then the 
corresponding word is selected as the suggestion
*/

void renSort(std::vector<std::vector<float>>& orderedVector);

bool randBool();
 
