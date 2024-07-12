#include <iostream>
#include <sstream>
#include <fstream>
#include "Markov.h"
#include <vector>

MarkovMatrix::MarkovMatrix(const char* fileName)
{
    loadFile(fileName);
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

void MarkovMatrix::calculateNodeProbabilites()
{
}

void MarkovMatrix::normalizeMatrix()
{
}

int main();
