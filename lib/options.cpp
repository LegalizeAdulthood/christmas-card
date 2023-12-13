#include "options.h"

#include <sstream>
#include <stdexcept>

namespace card
{

static Options g_options{};

void parseOptions(const std::vector<std::string_view> &args)
{
    for (size_t i = 1; i < args.size(); ++i)
    {
        std::string_view arg{args[i]};
        if (arg == "--debug")
        {
            g_options.debug = true;
        }
        if (arg == "--cursor")
        {
            if (i + 1 == args.size())
            {
                throw std::runtime_error("Missing value for --cursor argument");
            }
            std::istringstream str(args[i + 1].data());
            int                value{-1};
            str >> value;
            if (!str || value < SHOWCURSOR_HIDE || value > SHOWCURSOR_STANDOUT)
            {
                throw std::runtime_error(std::string{"Bad value for --cursor argument: "} + args[i + 1].data());
            }
            g_options.cursor = static_cast<ShowCursor>(value);
            ++i;
        }
    }
}

const Options &getOptions()
{
    return g_options;
}

} // namespace card
