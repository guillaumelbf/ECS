#include "App/app.hpp"

#include <iostream>

int main()
{
    try
    {
        App app;
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
