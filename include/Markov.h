#pragma once
#include <string>
#include <vector>

class initMarkovMatrix
{
    // --- properties
    std::string word;
        
public:
    int numUniqueWords;
    std::vector<std::string> fullWordList;
    std::vector<std::string> uniqueWordList;
    initMarkovMatrix(const char* fileName);

private:
    std::vector<std::string> loadFile(const char* FileName);
    std::vector<std::string> findUniqueWords(std::vector<std::string> wordList);
    void calculateNodeProbabilites();
};

class MarkovMatrix : public initMarkovMatrix
{

};