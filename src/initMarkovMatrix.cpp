#include <iostream>
#include <sstream>
#include <fstream>
#include <Markov.h>

MarkovMatrix::MarkovMatrix(const char* fileName)
{
    text = loadFile(fileName);
}

std::string MarkovMatrix::loadFile(const char* FileName)
{
    std::ifstream input;
    input.open(FileName);
    if (input.fail())
    {
        std::cerr << "[ERROR]: Could not open file. Check file name/directory" << std::endl;
        return 0;
    }
    else
    {
        std::stringstream ss;
        ss << input.rdbuf(); // store entire inputbuffer in the new stringstream object
        std::string fileContent = ss.str(); // gets content of stringstream object and returns it as a string
        input.close();
        return fileContent;
    }
}

void MarkovMatrix::tokenizeFile()
{
}

void MarkovMatrix::calculateNodeProbabilites()
{
}

void MarkovMatrix::normalizeMatrix()
{
}

int main();
