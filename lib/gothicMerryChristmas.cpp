#include "gothicMerryChristmas.h"

#include <curses.h>

#include <algorithm>
#include <chrono>
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

const char *const gothicMerryChristmas[] = {
    // clang-format off
    R"sprite(            /\\,/\\,)sprite",
    R"sprite(           /| || ||)sprite",
    R"sprite(           || || ||   _-_  ,._-_ ,._-_ '\\/\\)sprite",
    R"sprite(           ||=|= ||  || \\  ||    ||    || ;')sprite",
    R"sprite(          ~|| || ||  ||/    ||    ||    ||/)sprite",
    R"sprite(           |, \\,\\, \\,/   \\,   \\,   |/)sprite",
    R"sprite(          _-                           ()sprite",
    R"sprite(                                        -_-)sprite",
    R"sprite()sprite",
    R"sprite(  ,- _~. ,,                     ,)sprite",
    R"sprite( (' /|   ||           '        ||             _)sprite",
    R"sprite(((  ||   ||/\\ ,._-_ \\  _-_, =||= \\/\\/\\  < \,  _-_,)sprite",
    R"sprite(((  ||   || ||  ||   || ||_.   ||  || || ||  /-|| ||_.)sprite",
    R"sprite( ( / |   || ||  ||   ||  ~ ||  ||  || || || (( ||  ~ ||)sprite",
    R"sprite(  -____- \\ |/  \\,  \\ ,-_-   \\, \\ \\ \\  \/\\ ,-_-)sprite",
    R"sprite(           _/)sprite"
    // clang-format on
};

const int gothicMerryChristmasWidth = getSpriteWidth(gothicMerryChristmas);
const int gothicMerryChristmasHeight = getSpriteHeight(gothicMerryChristmas);

void renderGothicMerryChristmas(int frame)
{
    if (frame > 0)
    {
        move((frame - 1) % LINES, 0);
        clrtoeol();
    }
    const int x = (COLS - gothicMerryChristmasWidth) / 2 - 1;
    int       y{};

    for (int i = 0; i < gothicMerryChristmasHeight; ++i)
    {
        if (has_colors() && frame >= LINES)
        {
            if (y < 8)
            {
                attrset(COLOR_PAIR(1));
            }
            else
            {
                attrset(COLOR_PAIR(2));
            }
        }
        mvaddstr(frame % LINES + y, x, gothicMerryChristmas[i]);
        if (has_colors() && frame >= LINES)
        {
            attrset(A_NORMAL);
        }
        clrtoeol();
        ++y;
    }
}

} // namespace card
