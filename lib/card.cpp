#include <card.h>

#include "gothicMerryChristmas.h"

#include <curses.h>

#include <algorithm>
#include <cctype>
#include <chrono>
#include <string_view>

namespace card
{

using namespace std::chrono_literals;

using clock_t = std::chrono::high_resolution_clock;
using time_point_t = std::chrono::time_point<clock_t>;
using duration_t = clock_t::duration;

bool renderFrame(int frame)
{
    const time_point_t start{clock_t::now()};
    mvprintw(LINES - 1, 0, "Frame %d, LINES=%d, COLS=%d, ", frame, LINES, COLS);
    if (has_colors())
    {
        printw("color (%d colors, %d pairs)", COLORS, COLOR_PAIRS);
    }
    else
    {
        printw("B&W");
    }

    renderGothicMerryChristmas(frame);
    refresh();

    const duration_t duration = clock_t::now() - start;
    const auto       ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    napms(100 - static_cast<int>(ms));

    int ch = getch();
    return std::tolower(ch) == 'q';
}

int main()
{
    initscr();
    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
    }
    nodelay(stdscr, TRUE);

    bool quit{false};
    int  frame{};
    while (!quit)
    {
        quit = renderFrame(frame);
        ++frame;
    }

    endwin();
    return 0;
}

} // namespace card
