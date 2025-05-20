#include <iostream>

int main (int argc, char **argv)
{
    if (argc < 5)
        return std::cerr << "Error: not enough arguments !" << std::endl, 1;
    int i = 1;
    int j = 0;   
    while (argv[i])
    {
        while (argv[i][j])
        {
            
            ++j;
        }
        j = 0;
        ++i;
    }
}