#include <iostream>
#include <cstdlib>
#include "base/app.h"

int main(int argc, char *args[])
{
    App app;
    try
    {
        app.Run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}