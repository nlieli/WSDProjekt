#pragma once
#include <string>
#include <vector>

class MarkovMatrix
{
    // --- properties
    std::vector<std::string> tokenVector; //uses the vector template to create a custom vector type that takes std::string's as input
    std::string word;
        
public:
    int numUniqueWords;

    // --- methods
    MarkovMatrix(const char* fileName);

private:
    std::vector<std::string> loadFile(const char* FileName);
    void calculateNodeProbabilites();
    void normalizeMatrix();
};