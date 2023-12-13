#include "gothicMerryChristmas.h"

#include "options.h"

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

const int spriteWidth = getSpriteWidth(gothicMerryChristmas);
const int spriteHeight = getSpriteHeight(gothicMerryChristmas);

bool shouldRenderGothicMerryChristmas(int frame)
{
    return frame < (LINES + spriteHeight) * 3;
}

// Three phases of the animation
// 1. scroll partial sprite down from top
// 2. scroll sprite through window to bottom
// 3. scroll sprite off bottom
void renderGothicMerryChristmas(int frame)
{
    int phase = frame % (LINES + spriteHeight);
    int beginSpriteLine{};
    int endSpriteLine{spriteHeight};
    int startRow{0};
    // phase 1: sprite scrolling in from top
    if (phase < spriteHeight)
    {
        beginSpriteLine = spriteHeight - phase - 1;
    }
    // phase 2: sprite wholly on screen
    else if (phase < LINES)
    {
        startRow = phase - (spriteHeight - 1);
    }
    // phase 3: sprite scrolling off bottom
    else
    {
        endSpriteLine = phase - (LINES - spriteHeight) - 2;
        startRow = phase - (spriteHeight - 1);
    }
    if (getOptions().debug)
    {
        mvprintw(0, 0, "Phase: %d\nbegin %d, end %d\nstart %d", phase, beginSpriteLine, endSpriteLine, startRow);
        clrtoeol();
    }

    if (startRow > 0)
    {
        move(startRow - 1, 0);
        clrtoeol();
    }

    const int x{(COLS - spriteWidth) / 2 - 1};
    int       y{startRow};
    for (int i = beginSpriteLine; i < endSpriteLine; ++i)
    {
        if (has_colors() && frame >= (LINES + spriteHeight))
        {
            if (i < 8)
            {
                attrset(COLOR_PAIR(1));
            }
            else
            {
                attrset(COLOR_PAIR(2));
            }
        }
        mvaddstr(y, x, gothicMerryChristmas[i]);
        if (has_colors() && frame >= LINES)
        {
            attrset(A_NORMAL);
        }
        clrtoeol();
        ++y;
    }
}

} // namespace card
