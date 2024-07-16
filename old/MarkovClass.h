#pragma once
#include <string>
#include <vector>

// --- Miscellaneous functions
int findIndex(std::vector<std::string>& listOfWords, std::string searchItem);

// --- class definition

class MarkovMatrix
{
    // --- properties
public:

private:
    std::vector<std::string> fullWordList;
    std::vector<std::string> uniqueWordList;

    // --- methods
public:
    MarkovMatrix(const char* fileName);

private:
    std::vector<std::string> loadFile(const char* FileName);
    std::vector<std::string> findUniqueWords(std::vector<std::string> wordList);
    void createMatrix(std::vector<std::string>& UniqueWords, std::vector<std::string>& AllWords,
        std::vector<std::vector<float>>& Matrix, std::vector<int>& NormVector);
    void normalizeMatrix(std::vector<std::vector<float>>& Matrix, std::vector<int>& Vector);
    std::vector<float> initStateVector(std::string& word);
};
