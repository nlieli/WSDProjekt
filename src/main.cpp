#include "Markov.h"
#include <iostream>

int main()
{
    Timer timer;
    std::string currentWord;
    FileTokenizer FT;
    Markov Mv;

    FT.loadFile("../data/english/pg500.txt");

    Mv.updateMatrix(FT.m_uniqueWordMap, FT.m_fullWordList);

    for (;;)
    {
        std::cin >> currentWord;
        currentWord = "and";
        Mv.updateStateVector(FT.m_uniqueWordMap, currentWord);
        Mv.predictWord(FT.m_reverseUniqueMap, 3);
    }
    return 0;
}