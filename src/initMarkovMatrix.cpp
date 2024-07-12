#include <iostream>
#include <sstream>
#include <fstream>
#include "Markov.h"
#include <vector>
#include <algorithm>

using StringVector = std::vector<std::string>;

initMarkovMatrix::initMarkovMatrix(const char* fileName)
{   
    fullWordList = loadFile(fileName);
    uniqueWordList = findUniqueWords(fullWordList);
    numUniqueWords = uniqueWordList.size();
    
    // std::cout << fullWordList.size() << std::endl; 
    // std::cout << uniqueWordList.size() << std::endl; 
}

StringVector initMarkovMatrix::loadFile(const char* FileName)
{
    std::ifstream txtFileStream;
    txtFileStream.open(FileName);
    if (txtFileStream.fail())
    {
        std::cerr << "[ERROR]: Could not open file. Check file name/directory" << std::endl;
        return {};
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

StringVector initMarkovMatrix::findUniqueWords(StringVector wordList)
{
    sort(wordList.begin(), wordList.end());

    StringVector::iterator it; 
    it = std::unique(wordList.begin(), wordList.end()); // removes all but first element of every CONSECUTIVE group - also puts iterator at new past-the-end element 
    wordList.resize(distance(wordList.begin(), it)); // shortens the vector from beginning to new past-the-end flag element provided by iterator

    return wordList;
}

void initMarkovMatrix::calculateNodeProbabilites()
{
}

void initMarkovMatrix::normalizeMatrix()
{
}

int main();
