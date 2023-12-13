#include "wideMerryChristmas.h"

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

const char *const wideMerryChristmas[] = {
    // clang-format off
    R"sprite(88b           d88                                                   ,ad8888ba,  88                     88)sprite",
    R"sprite(888b         d888                                                  d8"'    `"8b 88                     ""             ,d)sprite",
    R"sprite(88`8b       d8'88                                                 d8'           88                                    88)sprite",
    R"sprite(88 `8b     d8' 88  ,adPPYba, 8b,dPPYba, 8b,dPPYba, 8b       d8    88            88,dPPYba,  8b,dPPYba, 88 ,adPPYba, MM88MMM 88,dPYba,,adPYba,  ,adPPYYba, ,adPPYba,)sprite",
    R"sprite(88  `8b   d8'  88 a8P_____88 88P'   "Y8 88P'   "Y8 `8b     d8'    88            88P'    "8a 88P'   "Y8 88 I8[    ""   88    88P'   "88"    "8a ""     `Y8 I8[    "")sprite",
    R"sprite(88   `8b d8'   88 8PP""""""" 88         88          `8b   d8'     Y8,           88       88 88         88  `"Y8ba,    88    88      88      88 ,adPPPPP88  `"Y8ba,)sprite",
    R"sprite(88    `888'    88 "8b,   ,aa 88         88           `8b,d8'       Y8a.    .a8P 88       88 88         88 aa    ]8I   88,   88      88      88 88,    ,88 aa    ]8I)sprite",
    R"sprite(88     `8'     88  `"Ybbd8"' 88         88             Y88'         `"Y8888Y"'  88       88 88         88 `"YbbdP"'   "Y888 88      88      88 `"8bbdP"Y8 `"YbbdP"')sprite",
    R"sprite(                                                       d8')sprite",
    R"sprite(                                                      d8')sprite"
    // clang-format on
};

int wideMerryChristmasWidth = getSpriteWidth(wideMerryChristmas);

void renderWideMerryChristmas(int frame)
{
    if (has_colors())
    {
        attrset(COLOR_PAIR(1));
    }

    static int lastStart{};
    if (frame > 0)
    {
        move(lastStart, 0);
        clrtoeol();
    }
    const int x = frame % wideMerryChristmasWidth;
    int       y{(LINES - getSpriteHeight(wideMerryChristmas)) / 2 - 1};
    lastStart = y;
    for (int i = 0; i < getSpriteHeight(wideMerryChristmas); ++i)
    {
        std::string_view line{wideMerryChristmas[i]};
        if (x > static_cast<int>(line.length()))
        {
            move(y, 0);
        }
        else
        {
            mvaddstr(y, 0, line.substr(x).data());
        }
        clrtoeol();
        ++y;
    }

    if (has_colors())
    {
        attrset(A_NORMAL);
    }
}

} // namespace card
