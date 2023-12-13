#include "card.h"

#include <algorithm>
#include <exception>
#include <iostream>

int main(int argc, char *argv[])
{
    std::vector<std::string_view> args;
    args.resize(argc);
    std::copy(&argv[0], &argv[argc], args.begin());
    try
    {
        return card::main(args);
    }
    catch (const std::exception &bang)
    {
        std::cerr << "Caught exception: " << bang.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown exception\n";
        return 1;
    }
}
