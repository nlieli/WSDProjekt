#pragma once
#include <string>
#include <vector>

using StringVector = std::vector<std::string>; //uses the vector template to create a custom vector type that takes std::string's as input

class initMarkovMatrix
{
    // --- properties
    std::string word;
        
public:
    int numUniqueWords;
    StringVector fullWordList;
    StringVector uniqueWordList;

    // --- methods
    initMarkovMatrix(const char* fileName);

private:
    StringVector loadFile(const char* FileName);
    StringVector findUniqueWords(StringVector wordList);
    void calculateNodeProbabilites();
    void normalizeMatrix();
};

class MarkovMatrix : public initMarkovMatrix {

};