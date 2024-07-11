#include <iostream>
#include "print.h"

int main()
{
    int a = 5;
    int* ptr = &a;
    int** ptr1 = &ptr;
    print(*ptr);
    const char* message = "yo";
    print(message);
    int yo = 10;
    print(yo);  
    std::cout << "Some other change" << std::endl;
    std::cout << "i dont even know";
}  