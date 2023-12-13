#pragma once

#include <string_view>
#include <vector>

namespace card
{

enum ShowCursor
{
    SHOWCURSOR_HIDE = 0,
    SHOWCURSOR_NORMAL = 1,
    SHOWCURSOR_STANDOUT = 2
};

struct Options
{
    bool       debug{};
    bool       singleStep{};
    ShowCursor cursor{SHOWCURSOR_HIDE};
};

void parseOptions(const std::vector<std::string_view> &args);
const Options &getOptions();

} // namespace card
