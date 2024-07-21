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
        int i = 0;
        ss << txtFileStream.rdbuf(); // store entire inputbuffer in the new stringstream object
        while (ss >> word) // ' ' is the delimiter, word is a variable that takes each tokenized input as definition 
        {
            m_fullWordList.push_back(word); // push_back creates new line in the vector and adds the token stored in word to the bottom    
            if (!m_uniqueWordMap.contains(word))
            {
                m_uniqueWordMap[word] = i;
                ++i;
            }
        }

        txtFileStream.close();

        m_totalCount = m_fullWordList.size();
        m_uniqueCount = m_uniqueWordMap.size();

        for (auto& element : m_uniqueWordMap)
            m_reverseUniqueMap[element.second] = element.first;

        std::cout << " Done!" << std::endl;
    }
}

/*
void FileTokenizer::findUniqueWords()
{
    Timer timer;
    std::cout << "Finding unique words...";
    m_uniqueWordMap = m_fullWordList;
    sort(m_uniqueWordMap.begin(), m_uniqueWordMap.end());

    StringVector_T::iterator it;
    it = std::unique(m_uniqueWordMap.begin(), m_uniqueWordMap.end()); // removes all but first element of every CONSECUTIVE group - also puts iterator at new past-the-end element
    m_uniqueWordMap.resize(distance(m_uniqueWordMap.begin(), it)); // shortens the vector from beginning to new past-the-end flag element provided by iterator
    m_uniqueCount = m_uniqueWordMap.size();
    std::cout << " Done!" << std::endl;
}
*/
void Markov::updateMatrix(std::unordered_map<std::string, int>& UniqueWords, StringVector_T& AllWords)
{
    Timer timer;
    std::cout << "Creating Matrix...\n";
    size_t n = UniqueWords.size();
    m_Matrix.resize(n, std::vector<float>(n));
    m_normVector.resize(n);

    size_t eof = AllWords.size();
    int j, k;
    float* ptr;
    m_pointerArray.resize(n);

    k = UniqueWords[AllWords[0]];

    for (size_t i = 1; i < eof; ++i)
    {
        j = UniqueWords[AllWords[i]];
        if (m_Matrix[j][k] < 1.0)
        {
            ptr = &m_Matrix[j][k];
            m_pointerArray[k].push_back(ptr);
        }

        ++m_Matrix[j][k];
        // ++m_normVector[k];
        k = j; // previous node exit becomes focus
    }

    normMat();
    // normalizeMatrix(m_Matrix);
}

void Markov::normMat()
{
    Timer timer;
    size_t n = m_pointerArray.size();

    for (size_t j = 0; j < n; ++j)
    {
        size_t m = m_pointerArray[j].size();
        int norm = 0;

        for (size_t i = 0; i < m; ++i)
            norm += *m_pointerArray[j][i];

        for (size_t k = 0; k < m; ++k)
        {
            *m_pointerArray[j][k] /= norm;
        }
    }
}
/*
void Markov::normalizeMatrix(std::vector<std::vector<float>>& Matrix)
{
    Timer timer;
    std::cout << " Done!" << "\nNormalizing Matrix...";
    size_t n_col = Matrix[0].size();
    size_t n_row = Matrix.size();
    for (size_t i = 0; i < n_row; ++i)
    {
        for (size_t j = 0; j < n_col; ++j)
        {
            if (m_normVector[j] > 0)
                Matrix[i][j] /= m_normVector[j];
        }
    }
    std::cout << " Done!" << std::endl;
}
*/
void Markov::updateStateVector(std::unordered_map<std::string, int>& wordList, std::string& inputWord)
{
    int i = wordList[inputWord];
    size_t n = wordList.size();
    m_stateVector.resize(n);

    for (size_t j = 0; j < n; ++j) // skip this loop on first call
        m_stateVector[j] = 0;
    m_stateVector[i] = 1;
}

/*
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
*/
void Markov::predictWord(std::unordered_map<int, std::string>& UniqueWords)
{
    size_t n = m_stateVector.size();
    FloatMatrix_T probVec(2, std::vector<float>(n));
    float randomProbabilityValue = randProb();
    std::string wordPrediction;
    float prob = 0;
    size_t pos;

    {
        std::cout << "Performing matrix multiplication...";
        Timer timer;
        m_stateVector = m_Matrix * m_stateVector;
        // m_stateVector = mtMm(m_Matrix, m_stateVector);
        std::cout << " Done!" << std::endl;
    }

    for (size_t i = 0; i < n; ++i)
        probVec[0][i] = i;

    probVec[1] = m_stateVector;
    int sortRange = preSort(probVec);
    quickSort(probVec, 0, sortRange);

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
