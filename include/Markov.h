#pragma once
#ifndef MARKOVMATRIX_H
#define MARKOVMATRIX_H

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
#endif