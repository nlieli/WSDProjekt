#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

struct FileTokenizer
{
    // --- properties
    std::vector<std::string> m_fullWordList;
    std::vector<std::string> m_uniqueWordList;

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

private:
    void normalizeMatrix(std::vector<std::vector<float>>& Matrix);
    int findIndex(std::vector<std::string>& listOfWords, std::string searchItem);
};

// --- Miscellaneous functions

