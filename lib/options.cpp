#include "options.h"

namespace card {

static Options g_options{};

void parseOptions(const std::vector<std::string_view> &args)
{
    for(std::string_view arg : args)
    {
        if (arg == "--debug")
        {
            g_options.debug = true;
        }
    }
}

const Options &getOptions()
{
    return g_options;
}

} //
