#include "Markov.h"
#include <iostream>

int main()
{
    Timer timer;
    std::string currentWord;
    FileTokenizer FT;
    Markov Mv;

    FT.loadFile("../data/english/pg4200.txt");

    Mv.updateMatrix(FT.m_uniqueWordMap, FT.m_fullWordList);

    // for (;;)
    // {
        // std::cin >> currentWord;
        currentWord = "here";
        Mv.updateStateVector(FT.m_uniqueWordMap, currentWord);
        Mv.predictWord(FT.m_reverseUniqueMap);
    // }
    // return 0;
}