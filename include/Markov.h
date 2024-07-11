#pragma once

class MarkovMatrix 
{
// --- properties
public:
    int wordCount;

// --- methods
    MarkovMatrix(const char* fileName);

private:
    int loadFile(const char* FileName);
    void tokenizeFile();
    void calculateNodeProbabilites();
    void normalizeMatrix();
};