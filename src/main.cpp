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

    for (;;)
    {
        std::cout << "Input seed word: ";
        std::cin >> currentWord;

        try {
            Mv.updateStateVector(FT.m_uniqueWordMap, currentWord);
        } 
        catch (const std::exception& e)
        {
                std::cout << "[Error]: Word is not in training list. Try again using a different word." << std::endl;
                continue;
        }

        Mv.predictWord(FT.m_reverseUniqueMap, 7);
    }
    return 0;
}