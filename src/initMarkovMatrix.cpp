#include <iostream>
#include <sstream>
#include <fstream>
#include <Markov.h>

MarkovMatrix::MarkovMatrix(const char* fileName)
{
    loadFile(fileName);
}

int MarkovMatrix::loadFile(const char* FileName)
{
    std::ifstream fileIn;
    fileIn.open(FileName);
    if (fileIn.fail())
    {
        std::cerr << "Check file name/directory";
        return 1;
    }

    fileIn.close();
    return 0;
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
