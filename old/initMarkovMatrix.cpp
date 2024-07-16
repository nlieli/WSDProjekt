#include <iostream>
#include <sstream>
#include <fstream>
#include "MarkovClass.h"
#include <vector>
#include <algorithm>

using StringVector = std::vector<std::string>;

// ---method definitions

MarkovMatrix::MarkovMatrix(const char* fileName)
{
    fullWordList = loadFile(fileName);
    uniqueWordList = findUniqueWords(fullWordList);

    size_t n = uniqueWordList.size();

    std::vector<std::vector<float>> Matrix(n, std::vector<float>(n)); // nxn Matrix
    std::vector<int> normVec(n); // vector that holds the normalization constant for each column of Matrix

    createMatrix(uniqueWordList, fullWordList, Matrix, normVec);
    normalizeMatrix(Matrix, normVec);
}

StringVector MarkovMatrix::loadFile(const char* FileName)
{
    std::string word;
    std::ifstream txtFileStream;
    txtFileStream.open(FileName);

    if (txtFileStream.fail())
    {
        std::cerr << "[ERROR]: Could not open file. Check file name/directory\n";
        return {}; // this is bad - it returns an empty vector but doesnt stop the program
    }
    else
    {
        std::stringstream ss;
        ss << txtFileStream.rdbuf(); // store entire inputbuffer in the new stringstream object
        StringVector tokenVector;
        while (std::getline(ss, word, ' ')) // ' ' is the delimiter, word is a variable that takes each tokenized input as definition 
        {
            tokenVector.push_back(word); // push_back creates new line in the vector and adds the token stored in word to the bottom    
        }

        txtFileStream.close();
        return tokenVector;
    }
}

StringVector MarkovMatrix::findUniqueWords(StringVector wordList)
{
    sort(wordList.begin(), wordList.end());

    StringVector::iterator it;
    it = std::unique(wordList.begin(), wordList.end()); // removes all but first element of every CONSECUTIVE group - also puts iterator at new past-the-end element 
    wordList.resize(distance(wordList.begin(), it)); // shortens the vector from beginning to new past-the-end flag element provided by iterator

    return wordList;
}

void MarkovMatrix::createMatrix(StringVector& UniqueWords, StringVector& AllWords, std::vector<std::vector<float>>& Matrix, std::vector<int>& NormVector)
{
    size_t eof = AllWords.size();
    int j, k;

    for (size_t i = 1; i < eof; i++)
    {
        j = k; // previous node exit becomes focus
        k = findIndex(UniqueWords, AllWords[i]);

        if (i == 1) // first word in file
            j = findIndex(UniqueWords, AllWords[0]);

        Matrix[j][k]++;
        NormVector[j]++;

        if (i == eof - 2) // prevents going out of bounds
            return;
    }
}

void MarkovMatrix::normalizeMatrix(std::vector<std::vector<float>>& Matrix, std::vector<int>& Vector)
{
   for (size_t j = 0; j < Matrix[0].size(); j++)
   {
        for (size_t i = 0; i < Matrix.size(); i++)
        {
           Matrix[i][j] = Matrix[i][j] / Vector[i];
        }
   } 
}

std::vector<float> MarkovMatrix::initStateVector(std::string& inputWord)
{
    int i = findIndex(uniqueWordList, inputWord);
    std::vector<float> stateVector(uniqueWordList.size());
    stateVector[i] = 1;
    return stateVector;
}

// --- Miscellaneous function

int findIndex(StringVector& listOfWords, std::string searchItem)
{
    int index;
    StringVector::iterator it;
    it = std::find(listOfWords.begin(), listOfWords.end(), searchItem);
    if (it != listOfWords.end())
    {
        index = it - listOfWords.begin();
    }
    else
    {
        std::cerr << "[ERROR]: Word \"" << searchItem << "\" was not found in training list\n";
        index = -1;
    }
    return index;
}
