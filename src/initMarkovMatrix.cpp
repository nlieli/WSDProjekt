#include <iostream>
#include <sstream>
#include <fstream>
#include "Markov.h"
#include <vector>
#include <algorithm>

MarkovMatrix::MarkovMatrix(const char* fileName)
{
    fullWordList = loadFile(fileName);
    uniqueWordList = findUniqueWords(fullWordList);

    std::cout << fullWordList.size() << std::endl; 
    std::cout << uniqueWordList.size() << std::endl; 
}

std::vector<std::string> MarkovMatrix::loadFile(const char* FileName)
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
        while (std::getline(ss, word, ' ')) // ' ' is the delimiter, word is a variable that takes each tokenized input as definition 
        {
            tokenVector.push_back(word); // push_back creates new line in the vector and adds the token stored in word to the bottom    
        }

        txtFileStream.close();
        return tokenVector;
    }
}

std::vector<std::string> MarkovMatrix::findUniqueWords(std::vector<std::string> wordList)
{
    //SORTING ALGORITHM NEEDED HERE


    std::vector<std::string>::iterator it; 
    it = std::unique(wordList.begin(), wordList.end()); // removes all but first element of every CONSECUTIVE group - also puts iterator at new past-the-end element 
    wordList.resize(distance(wordList.begin(), it)); // shortens the vector from beginning to new past-the-end flag element provided by iterator

    return wordList;
}

void MarkovMatrix::calculateNodeProbabilites()
{
}

void MarkovMatrix::normalizeMatrix()
{
}

int main();
