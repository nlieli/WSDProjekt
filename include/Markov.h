#pragma once
// #include <string>

class MarkovMatrix
{
    // --- properties
    std::string text;
        
public:
    int wordCount;

    // --- methods
    MarkovMatrix(const char* fileName);

private:
    std::string loadFile(const char* FileName);
    void tokenizeFile();
    void calculateNodeProbabilites();
    void normalizeMatrix();
};