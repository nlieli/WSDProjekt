#include "Markov.h"
#include <iostream>

int main()
{
    std::string currentWord;
    FileTokenizer FT;
    Markov Mv;

    FT.loadFile("../data/english/english_random_topic.txt");
    FT.findUniqueWords();

    Mv.updateMatrix(FT.m_uniqueWordList, FT.m_fullWordList);

    std::cin >> currentWord;
    Mv.updateStateVector(FT.m_uniqueWordList, currentWord);

    return 0;
} 