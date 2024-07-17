#include <iostream>
#include <sstream>
#include <fstream>
#include "Markov.h"
#include "Math.h"
#include <vector>
#include <algorithm>

using StringVector_T = std::vector<std::string>;
using FloatMatrix_T = std::vector<std::vector<float>>;
using IntMatrix_T = std::vector<std::vector<int>>;
using FloatVector_T = std::vector<float>;
using IntVector_T = std::vector<int>;

void FileTokenizer::loadFile(const char* fileName)
{
    std::string word;
    std::ifstream txtFileStream;
    std::stringstream ss;
    txtFileStream.open(fileName);

    if (txtFileStream.fail())
    {
        std::cerr << "[ERROR]: Could not open file. Check file name/directory\n";
        throw 2; 
    }
    else
    {
        ss << txtFileStream.rdbuf(); // store entire inputbuffer in the new stringstream object
        while (std::getline(ss, word, ' ')) // ' ' is the delimiter, word is a variable that takes each tokenized input as definition 
        {
            m_fullWordList.push_back(word); // push_back creates new line in the vector and adds the token stored in word to the bottom    
        }

        txtFileStream.close();
        m_totalCount = m_fullWordList.size();
    }
}

void FileTokenizer::findUniqueWords()
{
    m_uniqueWordList = m_fullWordList;
    sort(m_uniqueWordList.begin(), m_uniqueWordList.end());

    StringVector_T::iterator it;
    it = std::unique(m_uniqueWordList.begin(), m_uniqueWordList.end()); // removes all but first element of every CONSECUTIVE group - also puts iterator at new past-the-end element 
    m_uniqueWordList.resize(distance(m_uniqueWordList.begin(), it)); // shortens the vector from beginning to new past-the-end flag element provided by iterator
    m_uniqueCount = m_uniqueWordList.size();
}

void Markov::updateMatrix(StringVector_T& UniqueWords, StringVector_T& AllWords)
{
    size_t n = UniqueWords.size();
    m_Matrix.resize(n, std::vector<float>(n));
    m_normVector.resize(n);

    size_t eof = AllWords.size();
    int j, k;

    for (size_t i = 1; i < eof; i++)
    {
        j = k; // previous node exit becomes focus
        k = findIndex(UniqueWords, AllWords[i]);

        if (i == 1) // first word in file
            j = findIndex(UniqueWords, AllWords[0]);

        m_Matrix[j][k]++;
        m_normVector[j]++;

        if (i == eof - 2) // prevents going out of bounds
        {
            normalizeMatrix(m_Matrix);
            return;
        }
    }
}    

void Markov::normalizeMatrix(std::vector<std::vector<float>>& Matrix)
{
   for (size_t j = 0; j < Matrix[0].size(); j++)
   {
        for (size_t i = 0; i < Matrix.size(); i++)
        {
           Matrix[i][j] = Matrix[i][j] / m_normVector[i];
        }
   } 
} 

void Markov::updateStateVector(StringVector_T& wordList, std::string& inputWord)
{
    int i = findIndex(wordList, inputWord);
    m_stateVector.resize(wordList.size());
    m_stateVector[i] = 1;
}

int Markov::findIndex(StringVector_T& listOfWords, std::string searchItem)
{
    int index;
    StringVector_T::iterator it;
    it = std::find(listOfWords.begin(), listOfWords.end(), searchItem);
    if (it != listOfWords.end())
    {
        index = it - listOfWords.begin();
    }
    else
    {
        std::cerr << "[ERROR]: Word \"" << searchItem << "\" was not found in training list\n";
        throw 3;
    }
    return index;
}

void Markov::predictWord(StringVector_T& UniqueWords)
{
    size_t n = m_stateVector.size();
    FloatMatrix_T probVec(2, std::vector<float>(n));
    float randomProbabilityValue = randProb();
    std::string wordPrediction;

    m_stateVector = m_Matrix * m_stateVector;

    for (size_t i = 0; i < n; i++)
        probVec[0][i] = i;

    probVec[1] = m_stateVector;
    renSort(probVec);

    for (size_t j = 0; j < n; j++)
    {
        if (randomProbabilityValue < probVec[1][j])
        {
           wordPrediction = UniqueWords[probVec[0][j]];
           break;
        }
    }

    std::cout << wordPrediction << "\n";

}