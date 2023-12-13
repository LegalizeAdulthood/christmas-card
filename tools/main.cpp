#include "card.h"

#include <algorithm>

int main(int argc, char *argv[])
{
    std::vector<std::string_view> args;
    args.resize(argc);
    std::copy(&argv[0], &argv[argc], args.begin());
    return card::main(args);
}
