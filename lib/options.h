#pragma once

#include <string_view>
#include <vector>

namespace card
{

struct Options
{
    bool debug{};
};

void parseOptions(const std::vector<std::string_view> &args);
const Options &getOptions();

} // namespace card
