#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

/* 
The file tokenizer takes an input file and creates a token when it encounters a " ". These tokens
are then stored in a vector in the order of which they are encountered. This means in the same order that 
the text was written in the file. 

A copy of that list is made and sorted by their integer value. This allows for the use of the std::unique iterator.
*/
struct FileTokenizer
{
    // --- properties
    std::vector<std::string> m_fullWordList;
    std::vector<std::string> m_uniqueWordList;
    size_t m_totalCount;
    size_t m_uniqueCount;

    // --- methods 
    void loadFile(const char* fileName);
    void findUniqueWords();

};

// --- Markov class
class Markov
{
    // --- properties
public:
    std::vector<std::vector<float>> m_Matrix;
    std::vector<float> m_stateVector;

private:
    // std::vector<std::vector<int>> m_rawMatrix; //Might reinstate later to make additional features possible
    std::vector<int> m_normVector;
    // --- methods
public:
    void updateMatrix(std::vector<std::string>& UniqueWords,
        std::vector<std::string>& AllWords);
    void updateStateVector(std::vector<std::string>& wordList, std::string& inputWord);
    void predictWord(std::vector<std::string>& UniqueWords);

private:
    void normalizeMatrix(std::vector<std::vector<float>>& Matrix);
    int findIndex(std::vector<std::string>& listOfWords, std::string searchItem);
};

// --- Miscellaneous functions

