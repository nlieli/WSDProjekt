#include "Markov.h"
#include <iostream>

int main()
{
    Timer timer;
    std::string currentWord;
    FileTokenizer FT;
    Markov Mv;

    FT.loadFile("../data/english/pg100.txt");
    FT.findUniqueWords();

    Mv.updateMatrix(FT.m_uniqueWordList, FT.m_fullWordList);

    // for (;;)
    // {
        // std::cin >> currentWord;
        currentWord = "here";
        Mv.updateStateVector(FT.m_uniqueWordList, currentWord);
        Mv.predictWord(FT.m_uniqueWordList);
    // }
    // return 0;
}