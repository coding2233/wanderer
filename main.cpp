#include "base/app.h"

#include <iostream>
#include <cstdlib>

using namespace wanderer;

int main(int argc, char *args[])
{
    App app;
    try
    {
        app.Run(argc, args);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
