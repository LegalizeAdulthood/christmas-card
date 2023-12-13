#include "gothicMerryChristmas.h"

#include <curses.h>

#include <algorithm>
#include <cctype>
#include <chrono>
#include <string_view>

namespace card
{

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
    R"(          /| || ||)",
    R"(           || || ||   _-_  ,._-_ ,._-_ '\\/\\)",
    R"(           ||=|= ||  || \\  ||    ||    || ;')",
    R"(          ~|| || ||  ||/    ||    ||    ||/)",
    R"(           |, \\,\\, \\,/   \\,   \\,   |/)",
    R"(          _-                           ()",
    R"(                                        -_-)",
    R"()",
    R"(  ,- _~. ,,                     ,)",
    R"( (' /|   ||           '        ||             _)",
    R"(((  ||   ||/\\ ,._-_ \\  _-_, =||= \\/\\/\\  < \,  _-_,)",
    R"(((  ||   || ||  ||   || ||_.   ||  || || ||  /-|| ||_.)",
    R"( ( / |   || ||  ||   ||  ~ ||  ||  || || || (( ||  ~ ||)",
    R"(  -____- \\ |/  \\,  \\ ,-_-   \\, \\ \\ \\  \/\\ ,-_-)",
    R"(           _/)"
    // clang-format on
};

void renderGothicMerryChristmas(int frame)
{
    move((frame - 1) % LINES, 0);
    clrtoeol();
    const int x = (COLS - getSpriteWidth(gothicMerryChristmas)) / 2 - 1;
    int       y{};
    for (const char *line : gothicMerryChristmas)
    {
        if (frame >= LINES)
        {
            if (has_colors())
            {
                if (y < 7)
                {
                    attrset(COLOR_PAIR(1));
                }
                else
                {
                    attrset(COLOR_PAIR(2));
                }
            }
        }
        mvaddstr(frame % LINES + y, x, line);
        if (frame >= LINES)
        {
            if (has_colors())
            {
                attrset(A_NORMAL);
            }
        }
        clrtoeol();
        ++y;
    }
}

} // namespace card
