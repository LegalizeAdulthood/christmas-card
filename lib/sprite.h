#pragma once

#include <algorithm>
#include <string_view>

namespace card
{

template <int N>
int getSpriteHeight(const char *const (&)[N])
{
    return N;
}

template <int N>
int getSpriteWidth(const char *const (&text)[N])
{
    int maxWidth{};
    for (std::string_view line : text)
    {
        maxWidth = std::max(maxWidth, static_cast<int>(line.length()));
    }
    return maxWidth;
}

} // namespace card
