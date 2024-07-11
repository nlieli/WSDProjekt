#include <iostream>
#include "print.h"

void print(const char* myString)
{
    std::cout << static_cast<const void*>(myString) << std::endl;
}

void print(int &myValue)
{
    std::cout << myValue << std::endl;
}
