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
    std::cout << "Loading file contents...";
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
        std::cout << " Done!" << std::endl;
    }
}

void FileTokenizer::findUniqueWords()
{
    std::cout << "Finding unique words...";
    m_uniqueWordList = m_fullWordList;
    sort(m_uniqueWordList.begin(), m_uniqueWordList.end());

    StringVector_T::iterator it;
    it = std::unique(m_uniqueWordList.begin(), m_uniqueWordList.end()); // removes all but first element of every CONSECUTIVE group - also puts iterator at new past-the-end element 
    m_uniqueWordList.resize(distance(m_uniqueWordList.begin(), it)); // shortens the vector from beginning to new past-the-end flag element provided by iterator
    m_uniqueCount = m_uniqueWordList.size();
    std::cout << " Done!" << std::endl;
}

void Markov::updateMatrix(StringVector_T& UniqueWords, StringVector_T& AllWords)
{
    Timer timer;
    std::cout << "Creating Matrix...";
    size_t n = UniqueWords.size();
    m_Matrix.resize(n, std::vector<float>(n));
    m_normVector.resize(n);

    size_t eof = AllWords.size();
    int j, k;

    k = findIndex(UniqueWords, AllWords[0]);

    for (size_t i = 1; i < eof; ++i)
    {
        j = findIndex(UniqueWords, AllWords[i]);

        ++m_Matrix[j][k];
        ++m_normVector[k];
        k = j; // previous node exit becomes focus

        if (i == eof - 2) // prevents going out of bounds
        {
            normalizeMatrix(m_Matrix);
            return;
        }
    }
}

void Markov::normalizeMatrix(std::vector<std::vector<float>>& Matrix)
{
    Timer timer;
    std::cout << " Done!" << "\nNormalizing Matrix...";
    size_t n_col = Matrix[0].size();
    size_t n_row = Matrix.size();
    for (size_t j = 0; j < n_col; ++j)
    {
        for (size_t i = 0; i < n_row; ++i)
        {
            Matrix[i][j] /= m_normVector[j];
        }
    }
    std::cout << " Done!" << std::endl;
}

void Markov::updateStateVector(StringVector_T& wordList, std::string& inputWord)
{
    int i = findIndex(wordList, inputWord);
    size_t n = wordList.size();
    m_stateVector.resize(n);

    for (size_t j = 0; j < n; ++j)
        m_stateVector[j] = 0;
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
    float prob = 0;
    size_t pos;
    m_stateVector = m_Matrix * m_stateVector;

    for (size_t i = 0; i < n; ++i)
        probVec[0][i] = i;

    probVec[1] = m_stateVector;
    std::cout << "Sorting vector...";
    // renSort(probVec);
    int sortRange = preSort(probVec);
    // renSort(probVec, 0, sortRange);
    quickSort(probVec, 0, sortRange); // doesnt work atm

    std::cout << " Done!" << std::endl;
    for (size_t j = 0; j < n; ++j)
    {
        prob += probVec[1][j];
        if (randomProbabilityValue < prob)
        {
            wordPrediction = UniqueWords[probVec[0][j]];
            pos = j;
            break;
        }
    }

    std::cout << "\"" << wordPrediction << "\" " << " @ " << pos << " with likelihood " << probVec[1][pos] << "\n";

}

// --- Misc functions

Timer::Timer()
{
    start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    float ms = duration.count() * 999.0f;
    std::cout << "  execution time: " << ms << " ms" << std::endl;
}
