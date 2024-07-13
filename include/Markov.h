#pragma once
#include <string>
#include <vector>

int findIndex(std::vector<std::string>& listOfWords, std::string searchItem);

class initMarkovMatrix
{
    // --- properties
     
public:
    std::vector<std::string> fullWordList;
    std::vector<std::string> uniqueWordList;
    initMarkovMatrix(const char* fileName);

private:
    std::vector<std::string> loadFile(const char* FileName);
    std::vector<std::string> findUniqueWords(std::vector<std::string> wordList);
    void createMatrix(std::vector<std::string>& UniqueWords, std::vector<std::string>& AllWords, std::vector<std::vector<int>>& Matrix, std::vector<int>& NormVector);
    void calculateNodeProbabilites();
};
